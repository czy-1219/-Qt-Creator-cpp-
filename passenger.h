#ifndef PASSENGER_H
#define PASSENGER_H

#include "user.h"
#include <QList>
#include <QPair>

class Order;

class Passenger : public User
{
    Q_OBJECT//使用qt的槽必须使用该宏定义
public:
    Passenger(QObject *parent = nullptr);
    ~Passenger() override;

    void requestride(int startX, int startY, int endX, int endY, const QString &carType);
    void cancelorder(Order *order);

signals:
    void riderequested(int startX, int startY, int endX, int endY, const QString &carType);
    void ordercancelled(Order *order);

private:
};

#endif // PASSENGER_H
