#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H
#include "order.h"
#include <QObject>
#include <QList>
#include <QMap>
class Passenger;
class Driver;

class OrderManager : public QObject
{
    Q_OBJECT
public:
    static OrderManager *instance();

    Order *createorder(Passenger *passenger, int startX, int startY, int endX, int endY, const QString &cartype);
    Order *findorderbyid(const QString &id) const;
    QList<Order *> ordersbystatus(Order::Status status) const;
    QList<Order *> ordersbypassenger(Passenger *passenger) const;
    QList<Order *> ordersbydriver(Driver *driver) const;

    void addorder(Order *order);
    void updateorderstatus(Order *order, Order::Status status);
    void assigndrivertorder(Order *order, Driver *driver);
    void cancelorder(Order *order);
    void completeorder(Order *order);
signals:
    void ordercreated(Order *order);
    void orderstatuschanged(Order *order, Order::Status oldStatus, Order::Status newStatus);
    void orderassigned(Order *order, Driver *driver);
    void ordercancelled(Order *order);
    void ordercompleted(Order *order);

private:
    OrderManager(QObject *parent = nullptr);
    ~OrderManager() override;

    static OrderManager *m_instance;
    QMap<QString, Order *> m_orders;
    int m_orderCounter;
};

#endif // ORDERMANAGER_H
