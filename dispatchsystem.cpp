#include "dispatchsystem.h"
#include "order.h"
#include "driver.h"
#include "mapdata.h"
#include "ordermanager.h"
#include <algorithm>

DispatchSystem *DispatchSystem::m_instance = nullptr;

DispatchSystem::DispatchSystem(QObject *parent)//禁止手动delete有父对象的子对象，父对象必须是QObject子类
    : QObject(parent), m_mapData(MapData::instance())
{
    // 连接订单管理器的信号
    connect(OrderManager::instance(), &OrderManager::ordercreated, this, [this](Order *order) {
        // 当新订单创建时，将其添加到待派单列表
        dispatchorder(order);
    });
    
    // 连接订单状态变化信号
    connect(OrderManager::instance(), &OrderManager::orderstatuschanged, this, &DispatchSystem::onorderstatuschanged);
}

DispatchSystem::~DispatchSystem()
{
}

DispatchSystem *DispatchSystem::instance()
{
    if (!m_instance) {
        m_instance = new DispatchSystem();
    }
    return m_instance;
}

void DispatchSystem::registerdriver(Driver *driver)
{
    if (!m_registeredDrivers.contains(driver)) {
        m_registeredDrivers.append(driver);
        
        // 连接司机状态变化信号
        connect(driver, &QObject::destroyed, this, [this, driver]() {
            unregisterdriver(driver);
        });
        
        // 连接司机在线状态变化信号
        connect(driver, &Driver::onlinestatuschanged, this, &DispatchSystem::ondriveronlinestatuschanged);
        
        // 更新在线状态
        if (driver->isonline()) {
            m_onlineDrivers.append(driver);
            
            // 处理待处理订单
            handlependingorders();
        }
    }
}

void DispatchSystem::unregisterdriver(Driver *driver)
{
    m_registeredDrivers.removeAll(driver);
    m_onlineDrivers.removeAll(driver);
}

QList<Driver *> DispatchSystem::onlinedrivers() const
{
    return m_onlineDrivers;
}

QList<Order *> DispatchSystem::availableorders() const
{
    return m_availableOrders;
}

void DispatchSystem::dispatchorder(Order *order)
{
    if (order->status() != Order::Pending) {
        return; // 检查订单是否已经在分配中或已完成
    }
    // 平台操作模式：直接分配订单给最适合的司机
    QList<Driver *> candidates = filterdrivers(order);
    if (candidates.isEmpty()) {
        emit nodriveravailable(order);
        return;
    }
    // 按距离排序，选择最近的司机
    QList<QPair<Driver *, double>> scoredDrivers;
    for (Driver *driver : candidates) {
        double distance = calculatedistancetopassenger(driver, order);
        scoredDrivers.append(qMakePair(driver, distance));
    }
    
    // 按距离升序排列，最近的司机优先
    std::sort(scoredDrivers.begin(), scoredDrivers.end(), [](const QPair<Driver *, double> &a, const QPair<Driver *, double> &b) {
        return a.second < b.second; // 按距离升序排列
    });
    
    // 选择最近的司机
    Driver *selectedDriver = scoredDrivers.first().first;
    
    // 直接分配订单给选中的司机
    assignordertodriver(order, selectedDriver);
}

void DispatchSystem::assignordertodriver(Order *order, Driver *driver)
{
    // 将订单分配给指定的司机
    if (driver && driver->isonline() && !driver->hasactiveorder() && order->status() == Order::Pending) {
        // 1. 首先将订单从可用订单列表中移除，防止重复分配
        m_availableOrders.removeAll(order);
        emit availableordersupdated();
        
        // 2. 发出信号通知司机有新订单
        emit driverassigned(order, driver);
    }
}

void DispatchSystem::handledriverreject(Order *order, Driver *driver)
{
    // 司机拒绝订单，重新分配给其他司机
    
    // 清除司机的活跃订单状态
    if (driver->hasactiveorder()) {
        driver->clearactiveorder();
    }
    
    // 重置订单状态为待分配
    OrderManager::instance()->updateorderstatus(order, Order::Pending);
    order->setdriver(nullptr);
    
    // 将订单重新添加到可用订单列表
    if (!m_availableOrders.contains(order)) {
        m_availableOrders.append(order);
        emit availableordersupdated();
    }
    
    // 重新筛选候选司机，排除刚才拒绝的司机
    QList<Driver *> candidates = filterdrivers(order);
    candidates.removeAll(driver);
    
    if (candidates.isEmpty()) {
        emit nodriveravailable(order);
        return;
    }
    
    // 按距离排序，选择最近的司机
    QList<QPair<Driver *, double>> scoredDrivers;
    for (Driver *d : candidates) {
        double distance = calculatedistancetopassenger(d, order);
        scoredDrivers.append(qMakePair(d, distance));
    }
    
    // 按距离升序排列，最近的司机优先
    std::sort(scoredDrivers.begin(), scoredDrivers.end(), [](const QPair<Driver *, double> &a, const QPair<Driver *, double> &b) {
        return a.second < b.second; // 按距离升序排列
    });
    
    Driver *nextDriver = scoredDrivers.first().first;
    
    // 重新分配订单
    assignordertodriver(order, nextDriver);
}

void DispatchSystem::onorderstatuschanged(Order *order, int oldstatus, int newstatus)
{
    Q_UNUSED(oldstatus);
    
    // 如果订单状态不再是待派单，从可用订单列表中移除
    if (newstatus != Order::Pending) {
        m_availableOrders.removeAll(order);
        emit availableordersupdated();
    }
    
    // 如果订单被接受，确保其他司机的订单被取消，并通知其他司机
    if (newstatus == Order::Accepted) {
        // 获取接受订单的司机
        Driver *acceptedDriver = order->driver();
        bool hasOtherDrivers = false;
        
        // 遍历所有在线司机，检查是否有其他司机持有相同订单
        for (Driver *driver : m_onlineDrivers) {
            // 其他司机如果有相同的订单，清除活跃订单
            if (driver->hasactiveorder() && driver->currentorder() == order) {
                // 跳过接受订单的司机
                if (acceptedDriver && acceptedDriver == driver) {
                    continue;
                }
                // 有其他司机持有相同订单
                hasOtherDrivers = true;
                // 清除其他司机的活跃订单
                driver->clearactiveorder();
            }
        }
        
        // 只有当有其他司机持有相同订单时，才发出信号
        if (hasOtherDrivers) {
            emit orderacceptedbyother(order);
        }
    }
}

void DispatchSystem::ondriverstatuschanged()
{
    // 更新在线司机列表
    m_onlineDrivers.clear();
    for (Driver *driver : m_registeredDrivers) {
        if (driver->isonline()) {
            m_onlineDrivers.append(driver);
        }
    }
}

void DispatchSystem::ondriveronlinestatuschanged(bool online)
{
    Q_UNUSED(online);
    
    // 更新在线司机列表
    m_onlineDrivers.clear();
    for (Driver *driver : m_registeredDrivers) {
        if (driver->isonline()) {
            m_onlineDrivers.append(driver);
        }
    }
    
    // 如果司机上线，处理待处理订单
    if (online) {
        handlependingorders();
    }
}

void DispatchSystem::handlependingorders()
{
    // 只处理可用订单列表中的订单，避免重复分配
    QList<Order *> pendingOrders = availableorders();
    for (Order *order : pendingOrders) {
        // 重新派单
        dispatchorder(order);
    }
}

QList<Driver *> DispatchSystem::filterdrivers(Order *order)
{
    QList<Driver *> candidates;
    
    for (Driver *driver : m_onlineDrivers) {
        // 检查司机状态是否在线且空闲
        if (driver->status() != User::Online || driver->hasactiveorder()) {
            continue;
        }
        
        // 检查司机与乘客起点的距离是否在50以内
        double distance = calculatedistancetopassenger(driver, order);
        if (distance > 50.0) {
            continue;
        }
        

        
        candidates.append(driver);
    }
    
    return candidates;
}



double DispatchSystem::calculatedistancetopassenger(Driver *driver, Order *order)
{
    // 获取司机当前位置
    QPair<int, int> driverPos = driver->currentlocation();
    // 获取乘客起点
    QPair<int, int> passengerStart = order->startlocation(); 
    // 计算距离
    return m_mapData->calculatedistance(driverPos.first, driverPos.second,
                                      passengerStart.first, passengerStart.second);
}


