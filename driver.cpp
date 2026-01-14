#include "driver.h"
#include "order.h"

Driver::Driver(QObject *parent)
    : User(parent), m_isOnline(false), m_completedOrders(0), m_currentOrder(nullptr), m_totalMileage(0.0)
{
}

Driver::~Driver()
{
}

QString Driver::licenseplate() const
{
    return m_licensePlate;
}

void Driver::setlicenseplate(const QString &licenseplate)
{
    m_licensePlate = licenseplate;
}

QString Driver::carmodel() const
{
    return m_carModel;
}

void Driver::setcarmodel(const QString &carmodel)
{
    m_carModel = carmodel;
}

QPair<int, int> Driver::currentlocation() const
{
    return m_currentLocation;
}

void Driver::setcurrentlocation(int x, int y)
{
    m_currentLocation = qMakePair(x, y);
    emit locationupdated(x, y);
}

bool Driver::isonline() const
{
    return m_isOnline;
}

void Driver::setonline(bool online)
{
    if (m_isOnline != online) {
        m_isOnline = online;
        setstatus(online ? Online : Offline);
        emit onlinestatuschanged(online);
    }
}

void Driver::acceptorder(Order *order)
{
    setactiveorder(order);
    emit orderaccepted(order);
}

void Driver::rejectorder(Order *order)
{
    clearactiveorder();
    emit orderrejected(order);
}

void Driver::starttrip(Order *order)
{
    emit tripstarted(order);
}


int Driver::setcompletedorders(int n){
    m_completedOrders = n;
    return m_completedOrders;
}
void Driver::endtrip(Order *order)
{
    m_currentOrder = nullptr;
    setstatus(Online);
    incrementcompletedorders();
    
    // 添加当前订单的里程到累计里程中
    if (order) {
        addmileage(order->estimateddistance());
    }
    
    emit tripended(order);
}

int Driver::completedorders() const
{
    return m_completedOrders;
}

void Driver::incrementcompletedorders()
{
    m_completedOrders++;
}

bool Driver::hasactiveorder() const
{
    return m_currentOrder != nullptr;
}

Order *Driver::currentorder() const
{
    return m_currentOrder;
}

void Driver::setactiveorder(Order *order)
{
    m_currentOrder = order;
    if (order) {
        setstatus(Busy);
    } else {
        setstatus(Online);
    }
}

void Driver::clearactiveorder()
{
    m_currentOrder = nullptr;
    setstatus(Online);
}

// 累计里程相关方法实现
double Driver::totalmileage() const
{
    return m_totalMileage;
}

void Driver::addmileage(double mileage)
{
    m_totalMileage += mileage;
}

void Driver::settotalmileage(double mileage)
{
    m_totalMileage = mileage;
}
