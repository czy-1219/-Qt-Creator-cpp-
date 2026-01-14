#include "ordermanager.h"
#include "order.h"
#include "passenger.h"
#include "driver.h"
#include "dispatchsystem.h"
#include <QDateTime>
#include<QFile>
#include <QJsonArray>
#include <QJsonObject>
//Qmap是用于键值对有序关联容器，与map相同，会自动对「键」进行升序排序，map的有序序列有利查找
OrderManager *OrderManager::m_instance = nullptr;

OrderManager::OrderManager(QObject *parent)
    : QObject(parent), m_orderCounter(0)//订单计时器初始化为0
{
    // 初始化随机数种子，确保每次启动生成不同的随机数
    srand(QDateTime::currentMSecsSinceEpoch());
    // 连接订单创建信号到派单系统
    connect(this, &OrderManager::ordercreated, this, [](Order *order) {
        // 触发派单
        DispatchSystem::instance()->dispatchorder(order);
    });
}
OrderManager::~OrderManager()
{
    qDeleteAll(m_orders.values());//等价于遍历所有订单执行delete order
    m_orders.clear();
}

OrderManager *OrderManager::instance()
{
    if (!m_instance) {
        m_instance = new OrderManager();
    }
    return m_instance;
}

Order *OrderManager::createorder(Passenger *passenger, int startX, int startY, int endX, int endY, const QString &cartype)
{
    Order *order = new Order(this);
    // 生成唯一订单号：使用时间戳 + 随机数，确保重启后不会重复
    QDateTime now = QDateTime::currentDateTime();
    QString timestamp = now.toString("yyyyMMddHHmmsszzz");//now.toString("格式化格式")：QDateTime的格式化函数，把日期时间对象，按照指定的格式字符串
    QString randomPart = QString::number(rand() % 1000, 10).rightJustified(3, '0');
    QString orderId = QString("ORD%1%2").arg(timestamp).arg(randomPart);
    
    order->setid(orderId);
    order->setpassenger(passenger);
    order->setstartlocation(startX, startY);
    order->setendlocation(endX, endY);
    order->setcartype(cartype);
    order->setstatus(Order::Pending);
    order->setcreatedat(QDateTime::currentDateTime());
    // 计算并设置预估信息
    int segmentCount = abs(endX - startX) + abs(endY - startY);
    double distance = segmentCount * 3.0; // 3km
    double baseTime = segmentCount * 1.5; //每个网格单元1.5分钟
    double baseCost = segmentCount * 3.0; // 每段3元
    double adjustedTime = baseTime;
    double adjustedCost = baseCost;
    if (cartype == "专车") {
        // 专车：单价上浮20%，时间缩短10%
        adjustedTime = baseTime * 0.9;
        adjustedCost = baseCost * 1.2;
    }
    
    order->setestimateddistance(distance);
    order->setestimatedtime(adjustedTime);
    order->setestimatedcost(adjustedCost);

    m_orders.insert(orderId, order);

    // 连接订单状态变化信号
    connect(order, &Order::statuschanged, this, [this, order](Order::Status oldStatus, Order::Status newStatus) {
//参数4lambda 匿名槽函数，[] 是 lambda 的捕获列表，作用是：声明 lambda 内部可以访问哪些「外部变量」
//
        emit orderstatuschanged(order, oldStatus, newStatus);
    });

    emit ordercreated(order);
    return order;
}

Order *OrderManager::findorderbyid(const QString &id) const
{
    return m_orders.value(id, nullptr);//利用QMap的value()方法，通过订单 ID 快速查询
}

QList<Order *> OrderManager::ordersbystatus(Order::Status status) const
{
    QList<Order *> result;
    for (Order *order : m_orders.values()) {
        if (order->status() == status) {
            result.append(order);
        }
    }
    return result;
}

QList<Order *> OrderManager::ordersbypassenger(Passenger *passenger) const
{
    QList<Order *> result;
    for (Order *order : m_orders.values()) {
        if (order->passenger() == passenger) {
            result.append(order);
        }
    }
    return result;
}

QList<Order *> OrderManager::ordersbydriver(Driver *driver) const
{
    QList<Order *> result;
    for (Order *order : m_orders.values()) {
        if (order->driver() == driver) {
            result.append(order);
        }
    }
    return result;
}

void OrderManager::updateorderstatus(Order *order, Order::Status status)
{
    order->setstatus(status);
}

void OrderManager::addorder(Order *order)
{
    m_orders.insert(order->id(), order);
}

void OrderManager::assigndrivertorder(Order *order, Driver *driver)
{
    if (!m_orders.contains(order->id())) {
        addorder(order);
    }
    order->setdriver(driver);
    order->setstatus(Order::Accepted);
    order->setacceptedat(QDateTime::currentDateTime());
}

void OrderManager::cancelorder(Order *order)
{
    order->setstatus(Order::Cancelled);
    emit ordercancelled(order);
}
void OrderManager::completeorder(Order *order)
{
    // 设置实际费用为预估费用
    order->setactualcost(order->estimatedcost());
    order->setstatus(Order::Completed);
    order->setcompletedat(QDateTime::currentDateTime());
    emit ordercompleted(order);
}
