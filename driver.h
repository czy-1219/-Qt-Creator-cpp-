#ifndef DRIVER_H
#define DRIVER_H

#include "user.h"
#include <QPair>

class Order;

class Driver : public User
{
    Q_OBJECT
public:
    Driver(QObject *parent = nullptr);
    ~Driver() override;

    QString licenseplate() const;
    void setlicenseplate(const QString &licenseplate);

    QString carmodel() const;
    void setcarmodel(const QString &carmodel);

    QPair<int, int> currentlocation() const;
    void setcurrentlocation(int x, int y);

    bool isonline() const;
    void setonline(bool online);

    void acceptorder(Order *order);
    void rejectorder(Order *order);
    void starttrip(Order *order);
    void endtrip(Order *order);

    int completedorders() const;
    void incrementcompletedorders();
    int setcompletedorders(int n);
    bool hasactiveorder() const;
    Order *currentorder() const;
    void setactiveorder(Order *order);
    void clearactiveorder();
    
    // 累计里程相关方法
    double totalmileage() const;
    void addmileage(double mileage);
    void settotalmileage(double mileage);

signals:
    void orderaccepted(Order *order);
    void orderrejected(Order *order);
    void tripstarted(Order *order);
    void trippaused(Order *order);
    void tripended(Order *order);
    void locationupdated(int x, int y);
    void onlinestatuschanged(bool online);

private:
    QString m_licensePlate;
    QString m_carModel;
    QPair<int, int> m_currentLocation;
    bool m_isOnline;
    int m_completedOrders;
    Order *m_currentOrder;
    double m_totalMileage; // 累计里程（公里）
};

#endif // DRIVER_H
