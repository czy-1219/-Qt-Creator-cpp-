#ifndef ORDER_H
#define ORDER_H

#include <QObject>
#include <QDateTime>//统一处理日期 + 时间 + 时区
#include <QPair>

class Passenger;
class Driver;

class Order : public QObject
{
    Q_OBJECT
public:
    enum Status {
        Pending,
        Accepted,
        OnTheWay,
        PickingUp,
        InProgress,
        Completed,
        Cancelled
    };

    Order(QObject *parent = nullptr);
    ~Order() override;

    QString id() const;
    void setid(const QString &id);

    Passenger *passenger() const;
    void setpassenger(Passenger *passenger);

    Driver *driver() const;
    void setdriver(Driver *driver);

    QPair<int, int> startlocation() const;
    void setstartlocation(int x, int y);

    QPair<int, int> endlocation() const;
    void setendlocation(int x, int y);

    QString cartype() const;
    void setcartype(const QString &cartype);

    Status status() const;
    void setstatus(Status status);

    double estimateddistance() const;
    void setestimateddistance(double distance);

    double estimatedtime() const;
    void setestimatedtime(double time);

    double estimatedcost() const;
    void setestimatedcost(double cost);

    double actualcost() const;
    void setactualcost(double cost);

    double platformfee() const;
    double driverincome() const;

    QDateTime createdat() const;
    void setcreatedat(const QDateTime &time);

    QDateTime acceptedat() const;
    void setacceptedat(const QDateTime &time);

    QDateTime completedat() const;
    void setcompletedat(const QDateTime &time);
    
    QString driverid() const;
    void setdriverid(const QString &driverid);
    
    QString passengerid() const;
    void setpassengerid(const QString &passengerid);

signals://信号，没有函数体
    void statuschanged(Status oldStatus, Status newStatus);
    void driverassigned(Driver *driver);

private:
    QString m_id;
    Passenger *m_passenger;
    Driver *m_driver;
    QString m_driverId;
    QString m_passengerId;
    QPair<int, int> m_startLocation;
    QPair<int, int> m_endLocation;
    QString m_carType;
    Status m_status;
    double m_estimatedDistance;
    double m_estimatedTime;
    double m_estimatedCost;
    double m_actualCost; // 实际费用
    QDateTime m_createdAt;
    QDateTime m_acceptedAt;
    QDateTime m_completedAt;
};

#endif // ORDER_H
