#include "passenger.h"
#include "order.h"

Passenger::Passenger(QObject *parent)
    : User(parent)
{
}

Passenger::~Passenger()
{
}

void Passenger::requestride(int startX, int startY, int endX, int endY, const QString &carType)
{
    emit riderequested(startX, startY, endX, endY, carType);
}

void Passenger::cancelorder(Order *order)
{
    emit ordercancelled(order);//emit 触发信号槽
}


