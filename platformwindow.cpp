#include "platformwindow.h"
#include "passenger.h"
#include "ui_platformwindow.h"
#include "order.h"
#include "user.h"
#include "ordermanager.h"
#include "driver.h"
#include "dispatchsystem.h"
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include <QDateTime>
#include <QScrollBar>//滚动条的核心控件类
PlatformWindow::PlatformWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlatformWindow)
    , m_updateTimer(new QTimer(this))
{
    ui->setupUi(this);

    // 初始化地图场景
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->mapView->setScene(scene);
    ui->mapView->setSceneRect(0, 0, 900, 700);

    // 绘制简单的网格地图
    QPen gridPen(Qt::lightGray, 0.5);
    for (int x = 0; x <= 900; x += 50) {
        scene->addLine(x, 0, x, 700, gridPen);
    }
    for (int y = 0; y <= 700; y += 50) {
        scene->addLine(0, y, 900, y, gridPen);
    }

    // 设置定时器，每秒更新一次数据
    m_updateTimer->start(1000);
    connect(m_updateTimer, &QTimer::timeout, this, &PlatformWindow::updatedashboard);

    // 连接信号槽
    connect(OrderManager::instance(), &OrderManager::ordercreated, this, &PlatformWindow::onordercreated);
    connect(OrderManager::instance(), &OrderManager::orderstatuschanged, this, &PlatformWindow::onorderstatuschanged);

    // 初始更新
    updatedashboard();
}

PlatformWindow::~PlatformWindow()
{
    delete ui;
}

void PlatformWindow::updatedashboard()
{
    updateorderlist();
    updatedriverlist();
    updatemap();
    updatestats();
}

void PlatformWindow::onordercreated(Order *order)
{
    // 添加日志
    QString log = QString("%1 [订单创建] 订单ID: %2, 乘客: %3, 起点: (%4, %5), 终点: (%6, %7)")
        .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
        .arg(order->id())
        .arg(order->passenger()->name())
        .arg(order->startlocation().first)
        .arg(order->startlocation().second)
        .arg(order->endlocation().first)
        .arg(order->endlocation().second);
    ui->logTextEdit->append(log);
    
    // 滚动到底部
    ui->logTextEdit->verticalScrollBar()->setValue(ui->logTextEdit->verticalScrollBar()->maximum());
}

void PlatformWindow::onorderstatuschanged(Order *order, int oldstatus, int newstatus)
{
    QString oldStatusText, newStatusText;
    
    switch (oldstatus) {
    case Order::Pending: oldStatusText = "待派单"; break;
    case Order::Accepted: oldStatusText = "已接单"; break;
    case Order::OnTheWay: oldStatusText = "司机正在前往"; break;
    case Order::PickingUp: oldStatusText = "正在接驾"; break;
    case Order::InProgress: oldStatusText = "行程中"; break;
    case Order::Completed: oldStatusText = "已完成"; break;
    case Order::Cancelled: oldStatusText = "已取消"; break;
    default: oldStatusText = "未知状态"; break;
    }
    
    switch (newstatus) {
    case Order::Pending: newStatusText = "待派单"; break;
    case Order::Accepted: newStatusText = "已接单"; break;
    case Order::OnTheWay: newStatusText = "司机正在前往"; break;
    case Order::PickingUp: newStatusText = "正在接驾"; break;
    case Order::InProgress: newStatusText = "行程中"; break;
    case Order::Completed: newStatusText = "已完成"; break;
    case Order::Cancelled: newStatusText = "已取消"; break;
    default: newStatusText = "未知状态"; break;
    }
    
    // 添加日志
    QString log = QString("%1 [订单状态变更] 订单ID: %2, 从 '%3' 变更为 '%4'")
        .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
        .arg(order->id())
        .arg(oldStatusText)
        .arg(newStatusText);
    ui->logTextEdit->append(log);
    
    // 滚动到底部
    ui->logTextEdit->verticalScrollBar()->setValue(ui->logTextEdit->verticalScrollBar()->maximum());
}

void PlatformWindow::ondriverstatuschanged(Driver *driver)
{
    QString statusText;
    switch (driver->status()) {
    case User::Offline: statusText = "离线"; break;
    case User::Online: statusText = "在线"; break;
    case User::Busy: statusText = "忙碌"; break;
    default: statusText = "未知"; break;
    }
    
    // 添加日志
    QString log = QString("%1 [司机状态变更] 司机: %2, 车牌号: %3, 状态: %4")
        .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
        .arg(driver->name())
        .arg(driver->licenseplate())
        .arg(statusText);
    ui->logTextEdit->append(log);
    
    // 滚动到底部
    ui->logTextEdit->verticalScrollBar()->setValue(ui->logTextEdit->verticalScrollBar()->maximum());
}

void PlatformWindow::updateorderlist()
{
    ui->orderListWidget->clear();
    
    // 获取所有订单
    QList<Order *> orders = OrderManager::instance()->ordersbystatus(Order::Pending);
    orders.append(OrderManager::instance()->ordersbystatus(Order::Accepted));
    orders.append(OrderManager::instance()->ordersbystatus(Order::OnTheWay));
    orders.append(OrderManager::instance()->ordersbystatus(Order::PickingUp));
    orders.append(OrderManager::instance()->ordersbystatus(Order::InProgress));
    orders.append(OrderManager::instance()->ordersbystatus(Order::Completed));
    orders.append(OrderManager::instance()->ordersbystatus(Order::Cancelled));
    
    for (Order *order : orders) {
        QString statusText;
        Order::Status orderStatus = order->status();
        switch (orderStatus) {
        case Order::Pending: statusText = "待派单"; break;
        case Order::Accepted: statusText = "已接单"; break;
        case Order::OnTheWay: statusText = "司机正在前往"; break;
        case Order::PickingUp: statusText = "正在接驾"; break;
        case Order::InProgress: statusText = "行程中"; break;
        case Order::Completed: statusText = "已完成"; break;
        case Order::Cancelled: statusText = "已取消"; break;
        default: statusText = "未知状态"; break;
        }
        
        QString itemText;
        if (orderStatus == Order::Completed) {
            // 已完成订单显示抽成信息
            double cost = order->actualcost();
            double fee = order->platformfee();
            double driverIncome = order->driverincome();
            
            itemText = QString("%1 | %2 | 乘客: %3 | 起点: (%4, %5) | 终点: (%6, %7) | %8 | 费用: ¥%9 | 抽成: ¥%10 | 司机收入: ¥%11")
                .arg(order->id())
                .arg(statusText)
                .arg(order->passenger()->name())
                .arg(order->startlocation().first)
                .arg(order->startlocation().second)
                .arg(order->endlocation().first)
                .arg(order->endlocation().second)
                .arg(order->cartype())
                .arg(cost, 0, 'f', 2)
                .arg(fee, 0, 'f', 2)
                .arg(driverIncome, 0, 'f', 2);
        } else {
            // 未完成订单显示预估费用
            itemText = QString("%1 | %2 | 乘客: %3 | 起点: (%4, %5) | 终点: (%6, %7) | %8 | 预估费用: ¥%9")
                .arg(order->id())
                .arg(statusText)
                .arg(order->passenger()->name())
                .arg(order->startlocation().first)
                .arg(order->startlocation().second)
                .arg(order->endlocation().first)
                .arg(order->endlocation().second)
                .arg(order->cartype())
                .arg(order->estimatedcost(), 0, 'f', 2);
        }
        
        QListWidgetItem *item = new QListWidgetItem(itemText);
        ui->orderListWidget->addItem(item);
    }
}

void PlatformWindow::updatedriverlist()
{
    ui->driverListWidget->clear();
    
    // 获取所有在线司机
    QList<Driver *> drivers = DispatchSystem::instance()->onlinedrivers();
    
    for (Driver *driver : drivers) {
        QString statusText;
        switch (driver->status()) {
        case User::Offline: statusText = "离线"; break;
        case User::Online: statusText = "在线"; break;
        case User::Busy: statusText = "忙碌"; break;
        default: statusText = "未知"; break;
        }
        
        QString itemText = QString("%1 | %2 | 车牌号: %3 | 车型: %4 | 完成订单: %5 | 位置: (%6, %7)")
            .arg(driver->name())
            .arg(statusText)
            .arg(driver->licenseplate())
            .arg(driver->carmodel())
            .arg(driver->completedorders())
            .arg(driver->currentlocation().first)
            .arg(driver->currentlocation().second);
        
        QListWidgetItem *item = new QListWidgetItem(itemText);
        ui->driverListWidget->addItem(item);
    }
}

void PlatformWindow::updatemap()
{
    QGraphicsScene *scene = ui->mapView->scene();
    if (!scene) {
        return;
    }

    // 清除旧的标记
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        if (item->data(0).toString() == "driver" || item->data(0).toString() == "driverText" || 
            item->data(0).toString() == "driverCoord" || 
            item->data(0).toString() == "startPoint" || item->data(0).toString() == "endPoint" || 
            item->data(0).toString() == "startText" || item->data(0).toString() == "endText" || 
            item->data(0).toString() == "route") {
            scene->removeItem(item);
            delete item;
        }
    }

    // 绘制在线司机，区分不同司机
    QList<Driver *> drivers = DispatchSystem::instance()->onlinedrivers();
    
    // 准备不同的颜色，用于区分不同司机
    QList<QColor> driverColors = {Qt::blue, Qt::green, Qt::red, Qt::yellow, Qt::magenta, Qt::cyan, Qt::gray, Qt::darkRed, Qt::darkGreen, Qt::darkBlue};
    
    for (int i = 0; i < drivers.size(); ++i) {
        Driver *driver = drivers[i];
        QPair<int, int> pos = driver->currentlocation();
        
        // 直接使用网格坐标，转换为屏幕坐标
        double x = pos.first * 50;
        double y = pos.second * 50;
        
        // 根据司机状态选择颜色：忙碌为红色，其他为蓝色
        QColor color = (driver->status() == User::Busy) ? Qt::red : driverColors[i % driverColors.size()];
        
        // 司机用圆形表示，更加醒目
        QGraphicsEllipseItem *driverItem = new QGraphicsEllipseItem(x - 10, y - 10, 20, 20);
        driverItem->setPen(QPen(color, 2));
        driverItem->setBrush(QBrush(color, Qt::SolidPattern));
        driverItem->setData(0, "driver");
        scene->addItem(driverItem);
        
        // 添加司机名字标签，显示司机姓名
        QGraphicsTextItem *driverText = new QGraphicsTextItem(driver->name());
        driverText->setPos(x - 20, y - 30);
        driverText->setDefaultTextColor(color);
        driverText->setData(0, "driverText");
        scene->addItem(driverText);
        
        // 添加司机坐标标签，显示网格坐标
        QString coordText = QString("(%1,%2)").arg(pos.first).arg(pos.second);
        QGraphicsTextItem *coordItem = new QGraphicsTextItem(coordText);
        coordItem->setPos(x - 20, y + 15);
        coordItem->setDefaultTextColor(Qt::black);
        coordItem->setData(0, "driverCoord");
        scene->addItem(coordItem);
    }

    // 绘制订单
    QList<Order *> orders = OrderManager::instance()->ordersbystatus(Order::Pending);
    orders.append(OrderManager::instance()->ordersbystatus(Order::Accepted));
    orders.append(OrderManager::instance()->ordersbystatus(Order::OnTheWay));
    orders.append(OrderManager::instance()->ordersbystatus(Order::PickingUp));
    orders.append(OrderManager::instance()->ordersbystatus(Order::InProgress));
    
    for (Order *order : orders) {
        QPair<double, double> startPos = order->startlocation();
        QPair<double, double> endPos = order->endlocation();
        
        // 将经纬度转换为网格坐标（与乘客/司机窗口保持一致）
        int startGridX = qRound((startPos.second - 116.0) / 0.01);
        int startGridY = qRound((startPos.first - 39.0) / 0.01);
        int endGridX = qRound((endPos.second - 116.0) / 0.01);
        int endGridY = qRound((endPos.first - 39.0) / 0.01);
        
        // 转换为屏幕坐标
        double startX = startGridX * 50;
        double startY = startGridY * 50;
        double endX = endGridX * 50;
        double endY = endGridY * 50;
        
        // 绘制起点（绿色圆形，更大更醒目）
        QGraphicsEllipseItem *startItem = new QGraphicsEllipseItem(startX - 8, startY - 8, 16, 16);
        startItem->setPen(QPen(Qt::darkGreen, 2));
        startItem->setBrush(QBrush(Qt::green));
        startItem->setData(0, "startPoint");
        scene->addItem(startItem);
        
        // 添加起点文本标签
        QGraphicsTextItem *startText = new QGraphicsTextItem("起点");
        startText->setPos(startX - 15, startY - 25);
        startText->setDefaultTextColor(Qt::darkGreen);
        startText->setData(0, "startText");
        scene->addItem(startText);
        
        // 绘制终点（红色正方形，与起点区分）
        QGraphicsRectItem *endItem = new QGraphicsRectItem(endX - 8, endY - 8, 16, 16);
        endItem->setPen(QPen(Qt::darkRed, 2));
        endItem->setBrush(QBrush(Qt::red));
        endItem->setData(0, "endPoint");
        scene->addItem(endItem);
        
        // 添加终点文本标签
        QGraphicsTextItem *endText = new QGraphicsTextItem("终点");
        endText->setPos(endX - 15, endY - 25);
        endText->setDefaultTextColor(Qt::darkRed);
        endText->setData(0, "endText");
        scene->addItem(endText);
        
        // 绘制连线
        QPen routePen(Qt::blue, 2, Qt::DotLine);
        QGraphicsLineItem *line = scene->addLine(startX, startY, endX, endY, routePen);
        line->setData(0, "route");
    }
}

void PlatformWindow::updatestats()
{
    // 获取订单统计数据
    int totalOrders = OrderManager::instance()->ordersbystatus(Order::Pending).size() +
                     OrderManager::instance()->ordersbystatus(Order::Accepted).size() +
                     OrderManager::instance()->ordersbystatus(Order::OnTheWay).size() +
                     OrderManager::instance()->ordersbystatus(Order::PickingUp).size() +
                     OrderManager::instance()->ordersbystatus(Order::InProgress).size() +
                     OrderManager::instance()->ordersbystatus(Order::Completed).size() +
                     OrderManager::instance()->ordersbystatus(Order::Cancelled).size();
    
    int pendingOrders = OrderManager::instance()->ordersbystatus(Order::Pending).size();
    int acceptedOrders = OrderManager::instance()->ordersbystatus(Order::Accepted).size();
    int inProgressOrders = OrderManager::instance()->ordersbystatus(Order::InProgress).size();
    int completedOrders = OrderManager::instance()->ordersbystatus(Order::Completed).size();
    int onlineDrivers = DispatchSystem::instance()->onlinedrivers().size();
    
    // 更新UI
    ui->totalOrdersLabel->setText(QString("总订单数：%1").arg(totalOrders));
    ui->pendingOrdersLabel->setText(QString("待派单：%1").arg(pendingOrders));
    ui->acceptedOrdersLabel->setText(QString("已接单：%1").arg(acceptedOrders));
    ui->inProgressOrdersLabel->setText(QString("行程中：%1").arg(inProgressOrders));
    ui->completedOrdersLabel->setText(QString("已完成：%1").arg(completedOrders));
    ui->onlineDriversLabel->setText(QString("在线司机：%1").arg(onlineDrivers));
}
