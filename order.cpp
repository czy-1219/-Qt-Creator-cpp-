#include "order.h"
#include "passenger.h"
#include "driver.h"

Order::Order(QObject *parent)
    : QObject(parent), m_passenger(nullptr), m_driver(nullptr), m_status(Pending), m_actualCost(0.0)
{
}
Order::~Order()
{
}

QString Order::id() const
{
    return m_id;
}

void Order::setid(const QString &id)
{
    m_id = id;
}

Passenger *Order::passenger() const
{
    return m_passenger;
}

void Order::setpassenger(Passenger *passenger)
{
    m_passenger = passenger;
    if (passenger) {
        m_passengerId = passenger->id();
    } else {
        m_passengerId.clear();
    }
}

Driver *Order::driver() const
{
    return m_driver;
}

void Order::setdriver(Driver *driver)
{
    m_driver = driver;
    if (driver) {
        m_driverId = driver->id();
    } else {
        m_driverId.clear();
    }
    emit driverassigned(driver);//发射信号，其他模块可以通过槽函数接收这个信号
}

QPair<int, int> Order::startlocation() const
{
    return m_startLocation;
}

void Order::setstartlocation(int x, int y)
{
    m_startLocation = qMakePair(x, y);
}

QPair<int, int> Order::endlocation() const
{
    return m_endLocation;
}

void Order::setendlocation(int x, int y)
{
    m_endLocation = qMakePair(x, y);
}

QString Order::cartype() const
{
    return m_carType;
}

void Order::setcartype(const QString &cartype)
{
    m_carType = cartype;
}

Order::Status Order::status() const
{
    return m_status;
}

void Order::setstatus(Status status)
{
    if (m_status != status) {
        Status oldStatus = m_status;
        m_status = status;
        emit statuschanged(oldStatus, status);
    }
}

double Order::estimateddistance() const
{
    return m_estimatedDistance;
}

void Order::setestimateddistance(double distance)
{
    m_estimatedDistance = distance;
}

double Order::estimatedtime() const
{
    return m_estimatedTime;
}

void Order::setestimatedtime(double time)
{
    m_estimatedTime = time;
}

double Order::estimatedcost() const
{
    return m_estimatedCost;
}

void Order::setestimatedcost(double cost)
{
    m_estimatedCost = cost;
}

QDateTime Order::createdat() const
{
    return m_createdAt;
}

void Order::setcreatedat(const QDateTime &time)
{
    m_createdAt = time;
}

QDateTime Order::acceptedat() const
{
    return m_acceptedAt;
}

void Order::setacceptedat(const QDateTime &time)
{
    m_acceptedAt = time;
}

QDateTime Order::completedat() const
{
    return m_completedAt;
}

void Order::setcompletedat(const QDateTime &time)
{
    m_completedAt = time;
}

QString Order::driverid() const
{
    return m_driverId;
}

void Order::setdriverid(const QString &driverid)
{
    m_driverId = driverid;
}

QString Order::passengerid() const
{
    return m_passengerId;
}

void Order::setpassengerid(const QString &passengerid)
{
    m_passengerId = passengerid;
}

double Order::actualcost() const
{
    return m_actualCost;
}

void Order::setactualcost(double cost)
{
    m_actualCost = cost;
}
double Order::platformfee() const
{
    return m_actualCost * 0.3;
}

// 计算司机收入，实际费用减去平台抽成
double Order::driverincome() const
{
    return m_actualCost - platformfee();
}
