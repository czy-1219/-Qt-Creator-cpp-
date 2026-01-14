#ifndef DISPATCHSYSTEM_H
#define DISPATCHSYSTEM_H

#include <QObject>//信号槽，继承 QObject 的类必须声明 Q_OBJECT 宏，且需要运行 qmake 编译
#include <QList>//vector
#include <QPair>//pair Qt 二元组类

class Order;
class Driver;
class Passenger;
class MapData;

class DispatchSystem : public QObject
{
    Q_OBJECT
public:
    static DispatchSystem *instance();

    void registerdriver(Driver *driver);
    void unregisterdriver(Driver *driver);
    QList<Driver *> onlinedrivers() const;

    // 获取所有待派单的订单
    QList<Order *> availableorders() const;

    void dispatchorder(Order *order);
    void assignordertodriver(Order *order, Driver *driver);
    void handledriverreject(Order *order, Driver *driver);
    // 计算司机与乘客起点的距离
    double calculatedistancetopassenger(Driver *driver, Order *order);
signals:
    void driverassigned(Order *order, Driver *driver);
    void nodriveravailable(Order *order);

    // 可用订单列表更新信号
    void availableordersupdated();

    // 订单被接受信号，通知其他司机清除该订单
    void orderacceptedbyother(Order *order);

private slots:
    void ondriverstatuschanged();
    void ondriveronlinestatuschanged(bool online);
    void onorderstatuschanged(Order *order, int oldstatus, int newstatus);

private:
    DispatchSystem(QObject *parent = nullptr);
    ~DispatchSystem() override;

    static DispatchSystem *m_instance;
    QList<Driver *> m_registeredDrivers;
    QList<Driver *> m_onlineDrivers;
    MapData *m_mapData;

    // 待派单订单列表
    QList<Order *> m_availableOrders;

    // 筛选候选司机
    QList<Driver *> filterdrivers(Order *order);
    // 处理待处理订单
    void handlependingorders();
};

#endif // DISPATCHSYSTEM_H
