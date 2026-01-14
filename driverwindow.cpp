#include "driverwindow.h"
#include "ui_driverwindow.h"
#include "driver.h"
#include "order.h"
#include "user.h"
#include "passenger.h"
#include "ordermanager.h"
#include "pathplanner.h"
#include "dispatchsystem.h"
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include <QMessageBox>
#include <QTimer>
#include<QMouseEvent>
DriverWindow::DriverWindow(Driver *driver, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DriverWindow)
    , m_driver(driver)
    , m_currentOrder(nullptr)
    , m_locationTimer(new QTimer(this))
{
    ui->setupUi(this);

    // 设置初始状态
    ui->acceptOrderBtn->setEnabled(false);
    ui->rejectOrderBtn->setEnabled(false);
    ui->startTripBtn->setEnabled(false);
    ui->endTripBtn->setEnabled(false);
    ui->tripProgressBar->setValue(0);
    
    // 更新司机信息标签，显示实际的司机账号信息
    ui->driverInfoLabel->setText(QString("司机：%1 (%2) | %3 | %4").arg(m_driver->name()).arg(m_driver->id()).arg(m_driver->licenseplate()).arg(m_driver->carmodel()));
    
    // 初始化累计里程显示
    updatetotalmileage();

    // 初始化地图场景
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->mapView->setScene(scene);
    ui->mapView->setSceneRect(0, 0, 700, 500);
    m_scene = scene;
    
    // 绘制简单的网格地图（简化坐标）
    drawgridmap();
    
    // 添加地图点击事件
    ui->mapView->viewport()->installEventFilter(this);

    // 移除orderAccepted信号的连接，因为我们已经在on_acceptOrderBtn_clicked中完成了所有必要的操作
    // connect(m_driver, &Driver::orderAccepted, this, [this](Order *order) {
    //     m_currentOrder = order;
    //     updateOrderInfo(order);
    //     ui->acceptOrderBtn->setEnabled(false);
    //     ui->rejectOrderBtn->setEnabled(false);
    //     ui->startTripBtn->setEnabled(false); // 初始禁用，到达起点后启用
    //     
    //     // 规划路径并开始移动
    //     startDriverMovement();
    // });

    connect(m_driver, &Driver::orderrejected, this, [this](Order *order) {
        Q_UNUSED(order);
        m_currentOrder = nullptr;
        ui->acceptOrderBtn->setEnabled(false);
        ui->rejectOrderBtn->setEnabled(false);
    });

    connect(m_locationTimer, &QTimer::timeout, this, &DriverWindow::updatelocation);

    // 连接订单管理器的信号
    connect(OrderManager::instance(), &OrderManager::orderstatuschanged, this, &DriverWindow::onorderstatuschanged);

    // 连接派单系统的信号，只有当订单分配给当前司机时才处理
    connect(DispatchSystem::instance(), &DispatchSystem::driverassigned, this, [this](Order *order, Driver *driver) {
        // 只有当订单分配给当前司机时才处理
        qDebug() << "Driver assigned signal received. Order: " << order->id() << ", Assigned driver: " << driver->id() << ", Current driver: " << m_driver->id();
        if (driver->id() == m_driver->id()) {
            qDebug() << "Order is for current driver, showing popup.";
            onorderassigned(order);
        } else {
            qDebug() << "Order is not for current driver, ignoring.";
        }
    });
    connect(DispatchSystem::instance(), &DispatchSystem::availableordersupdated, this, &DriverWindow::updateavailableorders);
    connect(DispatchSystem::instance(), &DispatchSystem::availableordersupdated, this, &DriverWindow::updatemapmarkers);
    connect(DispatchSystem::instance(), &DispatchSystem::orderacceptedbyother, this, &DriverWindow::onotherdriveracceptedorder);
    
    // 初始化司机位置标记
    updatemapmarkers();
}

DriverWindow::~DriverWindow()
{
    // 确保司机下线时清理资源
    if (m_driver->isonline()) {
        // 从派单系统注销司机
        DispatchSystem::instance()->unregisterdriver(m_driver);
    }
    
    // 清理当前订单
    m_currentOrder = nullptr;
    m_currentPath.clear();
    m_currentPathIndex = 0;
    m_hasArrivedAtStart = false;
    
    delete ui;
}

void DriverWindow::drawgridmap()
{
    // 不要清除现有内容，避免路线被清除
    
    // 绘制简单的网格地图（简化坐标）
    QPen gridPen(Qt::lightGray, 0.5);
    int gridSize = 50; // 网格大小
    int width = 700;
    int height = 500;
    
    // 绘制网格线
    for (int x = 0; x <= width; x += gridSize) {
        m_scene->addLine(x, 0, x, height, gridPen);
    }
    for (int y = 0; y <= height; y += gridSize) {
        m_scene->addLine(0, y, width, y, gridPen);
    }
    
    // 绘制网格坐标标签（简化）
    QPen textPen(Qt::gray);
    QFont font("Arial", 8);
    for (int x = 0; x <= width; x += gridSize) {
        for (int y = 0; y <= height; y += gridSize) {
            // 简化坐标：使用网格索引作为坐标
            int gridX = x / gridSize;
            int gridY = y / gridSize;
            QString coordText = QString("(%1,%2)").arg(gridX).arg(gridY);
            QGraphicsTextItem *textItem = m_scene->addText(coordText, font);
            textItem->setPos(x + 2, y + 2);
            textItem->setDefaultTextColor(Qt::gray);
        }
    }
    
    // 初始化标记
    m_driverMarker = nullptr;
    m_driverText = nullptr;
    m_passengerMarkers.clear();
    m_passengerTexts.clear();
    m_destinationTexts.clear();
    m_routeLines.clear();
}

QPair<int, int> DriverWindow::screentomap(const QPointF &screenPos)
{
    // 将屏幕坐标转换为网格坐标
    int gridSize = 50;
    int gridX = qRound(screenPos.x() / gridSize);
    int gridY = qRound(screenPos.y() / gridSize);
    
    return qMakePair(gridX, gridY);
}

QPointF DriverWindow::maptoscreen(const QPair<int, int> &mapPos)
{
    // 将网格坐标转换为屏幕坐标
    int gridSize = 50;
    return QPointF(mapPos.first * gridSize, mapPos.second * gridSize);
}

void DriverWindow::updatemapmarkers()
{
    // 移除旧的司机标记
    if (m_driverMarker) {
        m_scene->removeItem(m_driverMarker);
        delete m_driverMarker;
        m_driverMarker = nullptr;
    }
    
    // 移除旧的司机文字标记
    if (m_driverText) {
        m_scene->removeItem(m_driverText);
        delete m_driverText;
        m_driverText = nullptr;
    }
    
    // 移除旧的乘客标记
    for (QGraphicsEllipseItem *marker : m_passengerMarkers) {
        m_scene->removeItem(marker);
        delete marker;
    }
    m_passengerMarkers.clear();
    
    // 移除旧的乘客文字标记
    for (QGraphicsTextItem *text : m_passengerTexts) {
        m_scene->removeItem(text);
        delete text;
    }
    m_passengerTexts.clear();
    
    // 移除旧的终点文字标记
    for (QGraphicsTextItem *text : m_destinationTexts) {
        m_scene->removeItem(text);
        delete text;
    }
    m_destinationTexts.clear();
    
    // 只有在没有当前订单时才清除路线线条
    if (!m_currentOrder) {
        // 移除旧的路线线条
        for (QGraphicsLineItem *line : m_routeLines) {
            m_scene->removeItem(line);
            delete line;
        }
        m_routeLines.clear();
    }
    
    // 绘制司机位置标记
    QPair<int, int> driverPos = m_driver->currentlocation();
    QPointF driverScreenPos = maptoscreen(driverPos);
    m_driverMarker = m_scene->addEllipse(driverScreenPos.x() - 10, driverScreenPos.y() - 10, 20, 20, QPen(Qt::blue), QBrush(Qt::blue));
    m_driverText = m_scene->addText("司机");
    m_driverText->setPos(driverScreenPos.x() - 15, driverScreenPos.y() - 30);
    
    // 只显示当前分配的订单，不显示所有可用订单
    if (m_currentOrder) {
        // 绘制乘客起点位置
        QPair<int, int> startPos = m_currentOrder->startlocation();
        QPointF startScreenPos = maptoscreen(startPos);
        QGraphicsEllipseItem *passengerMarker = m_scene->addEllipse(startScreenPos.x() - 8, startScreenPos.y() - 8, 16, 16, QPen(Qt::green), QBrush(Qt::green));
        m_passengerMarkers.append(passengerMarker);
        
        QGraphicsTextItem *passengerText = m_scene->addText("乘客");
        passengerText->setPos(startScreenPos.x() - 15, startScreenPos.y() - 30);
        m_passengerTexts.append(passengerText);
        
        // 绘制乘客终点位置
        QPair<int, int> endPos = m_currentOrder->endlocation();
        QPointF endScreenPos = maptoscreen(endPos);
        QGraphicsEllipseItem *destinationMarker = m_scene->addEllipse(endScreenPos.x() - 8, endScreenPos.y() - 8, 16, 16, QPen(Qt::red), QBrush(Qt::red));
        m_passengerMarkers.append(destinationMarker);
        
        QGraphicsTextItem *destinationText = m_scene->addText("终点");
        destinationText->setPos(endScreenPos.x() - 15, endScreenPos.y() - 30);
        m_destinationTexts.append(destinationText);
        
        // drawRoute方法会绘制更详细的路径，包括司机到乘客起点的路径
    }
    
    // 如果有活跃订单且有当前路径，重新绘制详细路线
    if (m_driver->hasactiveorder() && !m_currentPath.isEmpty()) {
        redrawcurrentroute();
    }
}

bool DriverWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->mapView->viewport() && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            // 只有当司机离线时，才允许通过点击地图修改自己的位置
            if (!m_driver->isonline()) {
                // 获取点击位置
                QPointF scenePos = ui->mapView->mapToScene(mouseEvent->pos());
                QPair<int, int> mapPos = screentomap(scenePos);
                
                // 设置司机启动位置
                m_driver->setcurrentlocation(mapPos.first, mapPos.second);
                updatemapmarkers();
                
                return true;
            }
        }
    }
    
    return QMainWindow::eventFilter(obj, event);
}

void DriverWindow::on_onlineBtn_clicked()
{
    bool isOnline = m_driver->isonline();
    
    if (!isOnline) {
        // 检查是否已经选择了启动地点
        QPair<int, int> currentPos = m_driver->currentlocation();
        // 检查是否是默认位置（0, 0）
        if (currentPos.first == 0 && currentPos.second == 0) {
            QMessageBox::warning(this, "提示", "请先在地图上选择启动地点！");
            return;
        }
    }
    
    m_driver->setonline(!isOnline);
    
    if (m_driver->isonline()) {
        ui->onlineBtn->setText("下线");
        ui->onlineBtn->setStyleSheet("background-color: red; color: white;");
        ui->statusLabel->setText("当前状态：在线");
        
        // 注册司机到派单系统
        DispatchSystem::instance()->registerdriver(m_driver);
        
        // 启动位置更新定时器，减慢移动速度
        m_locationTimer->start(1000);
        
        // 更新地图标记
        updatemapmarkers();
    } else {
        ui->onlineBtn->setText("上线");
        ui->onlineBtn->setStyleSheet("background-color: green; color: white;");
        ui->statusLabel->setText("当前状态：离线");
        
        // 从派单系统注销司机
        DispatchSystem::instance()->unregisterdriver(m_driver);
        
        // 停止位置更新定时器
        m_locationTimer->stop();
        
        // 清理当前订单
        m_currentOrder = nullptr;
        m_currentPath.clear();
        m_currentPathIndex = 0;
        m_hasArrivedAtStart = false;
        
        // 清除地图标记
        drawgridmap();
    }
}

void DriverWindow::on_acceptOrderBtn_clicked()
{
    qDebug() << "开始处理接单请求...";
    
    if (!m_currentOrder || m_driver->hasactiveorder()) {
        qDebug() << "当前没有订单或司机已有活跃订单，返回";
        return;
    }
    
    // 立即禁用所有按钮，防止任何点击操作
    ui->acceptOrderBtn->setEnabled(false);
    ui->rejectOrderBtn->setEnabled(false);
    ui->startTripBtn->setEnabled(false);
    ui->endTripBtn->setEnabled(false);
    
    qDebug() << "按钮已禁用";
    
    // 保存当前订单和司机位置
    Order *order = m_currentOrder;
    QPair<int, int> driverPos = m_driver->currentlocation();
    QPair<int, int> startPos = order->startlocation();
    QPair<int, int> endPos = order->endlocation();
    
    qDebug() << "获取订单和司机位置成功";
    
    // 使用PathPlanner来规划路径，与onOrderAssigned函数保持一致
    QList<QPair<int, int>> path1 = PathPlanner::instance()->planpath(driverPos.first, driverPos.second, startPos.first, startPos.second);
    QList<QPair<int, int>> path2 = PathPlanner::instance()->planpath(startPos.first, startPos.second, endPos.first, endPos.second);
    
    // 合并路径，确保路径至少有两个点
    QList<QPair<int, int>> fullPath = path1;
    if (!path2.isEmpty()) {
        fullPath.append(path2.mid(1));
    }
    
    // 确保路径至少有两个点
    if (fullPath.size() < 2) {
        if (fullPath.isEmpty()) {
            fullPath.append(driverPos);
        }
        if (fullPath.size() == 1) {
            fullPath.append(endPos);
        }
    }
    
    qDebug() << "路径规划成功，路径长度:" << fullPath.size();
    
    // 2. 最后更新所有状态，避免信号冲突
    m_currentOrder = order;
    m_currentPath = fullPath;
    m_currentPathIndex = 0;
    
    qDebug() << "状态更新成功";
    
    // 检查司机当前位置是否已经在起点
    if (driverPos.first == startPos.first && driverPos.second == startPos.second) {
        m_hasArrivedAtStart = true;
        ui->startTripBtn->setEnabled(true);
        ui->tripStatusLabel->setText("行程状态：已到达起点，可开始行程");
        qDebug() << "司机已到达起点，开始行程按钮已启用";
    } else {
        m_hasArrivedAtStart = false;
        ui->startTripBtn->setEnabled(false);
        ui->tripStatusLabel->setText("行程状态：已接单，前往起点中");
        qDebug() << "司机未到达起点，开始行程按钮已禁用";
    }
    
    // 设置订单状态和司机状态
    order->setdriver(m_driver);
    order->setstatus(Order::Accepted);
    order->setacceptedat(QDateTime::currentDateTime());
    
    qDebug() << "订单状态和司机状态设置成功";
    
    // 3. 确保位置更新定时器正在运行，这样司机才能自动移动
    if (!m_locationTimer->isActive()) {
        m_locationTimer->start(1000);
        qDebug() << "位置更新定时器已启动";
    }
    
    // 添加调试信息
    qDebug() << "订单路径规划成功，路径长度:" << fullPath.size();
    for (int i = 0; i < fullPath.size(); i++) {
        qDebug() << "路径点" << i << ":" << fullPath[i].first << "," << fullPath[i].second;
    }
    

    drawroute(fullPath);

    updatemapmarkers();
    updateorderinfo(order);

    // 最后调用acceptorder函数，触发orderaccepted信号，此时所有状态都已正确设置
    m_driver->acceptorder(order);

}

void DriverWindow::on_rejectOrderBtn_clicked()
{
    if (!m_currentOrder) {
        return;
    }
    
    // 先处理拒绝逻辑
    Order *order = m_currentOrder;
    m_currentOrder = nullptr;
    m_driver->rejectorder(order);
    DispatchSystem::instance()->handledriverreject(order, m_driver);
    
    // 清除当前订单和路线
        m_currentPath.clear();
        m_currentPathIndex = 0;
        m_hasArrivedAtStart = false;
        
        // 更新UI状态
        ui->acceptOrderBtn->setEnabled(false);
        ui->rejectOrderBtn->setEnabled(false);
        ui->tripStatusLabel->setText("行程状态：无订单");
        
        // 清除订单信息
        ui->orderIdLabel->setText("订单编号：无");
        ui->passengerInfoLabel->setText("乘客：无");
        ui->startLocationLabel->setText("起点：无");
        ui->endLocationLabel->setText("终点：无");
        ui->estimatedDistanceLabel->setText("预估距离：0.0 km");
        ui->estimatedTimeLabel->setText("预估时长：0.0 分钟");
        ui->tripProgressBar->setValue(0);
        
        // 彻底清除地图上的路线和标记
        m_scene->clear();
        drawgridmap();
        
        // 重新绘制地图标记，只显示司机位置和可选订单
        updatemapmarkers();

}

void DriverWindow::onotherdriveracceptedorder(Order *order)
{
    // 如果当前没有订单或者传入订单为空，直接返回
    if (!m_currentOrder || !order) {
        return;
    }
    
    // 如果当前订单是其他司机接受的订单，清除它
    if (m_currentOrder == order) {
        // 清除当前订单和路线
        m_currentOrder = nullptr;
        m_currentPath.clear();
        m_currentPathIndex = 0;
        m_hasArrivedAtStart = false;
        
        // 更新UI状态
        ui->acceptOrderBtn->setEnabled(false);
        ui->rejectOrderBtn->setEnabled(false);
        ui->tripStatusLabel->setText("行程状态：订单已被其他司机接受");
        
        // 清除订单信息
        ui->orderIdLabel->setText("订单编号：无");
        ui->passengerInfoLabel->setText("乘客：无");
        ui->startLocationLabel->setText("起点：无");
        ui->endLocationLabel->setText("终点：无");
        ui->estimatedDistanceLabel->setText("预估距离：0.0 km");
        ui->estimatedTimeLabel->setText("预估时长：0.0 分钟");
        ui->tripProgressBar->setValue(0);
        
        // 彻底清除地图上的路线和标记
        m_scene->clear();
        drawgridmap();
        
        // 重新绘制地图标记，只显示司机位置和可选订单
        updatemapmarkers();
    }
}

void DriverWindow::on_startTripBtn_clicked()
{
    if (m_currentOrder) {
        // 检查是否已到达起点
        if (!m_hasArrivedAtStart) {
            QMessageBox::warning(this, "提示", "尚未到达起点，无法开始行程！");
            return;
        }
        
        m_driver->starttrip(m_currentOrder);
        OrderManager::instance()->updateorderstatus(m_currentOrder, Order::InProgress);
        ui->tripStatusLabel->setText("行程状态：进行中");
        ui->startTripBtn->setEnabled(false);
        ui->endTripBtn->setEnabled(false); // 初始禁用，到达终点后启用
    }
}

void DriverWindow::on_endTripBtn_clicked()
{
    if (m_currentOrder) {
        // 检查是否已到达终点
        QPair<int, int> currentPos = m_driver->currentlocation();
        QPair<int, int> endPos = m_currentOrder->endlocation();
        
        // 使用直接比较检查是否到达终点，因为网格坐标是整数
        if (currentPos.first != endPos.first || currentPos.second != endPos.second) {
            QMessageBox::warning(this, "提示", "尚未到达终点，无法结束行程！");
            return;
        }
        
        m_driver->endtrip(m_currentOrder);
        OrderManager::instance()->completeorder(m_currentOrder);
        ui->tripStatusLabel->setText("行程状态：已完成");
        ui->tripProgressBar->setValue(100);
        ui->startTripBtn->setEnabled(false);
        ui->endTripBtn->setEnabled(false);
        
        m_currentOrder = nullptr;
        m_currentPath.clear();
        m_currentPathIndex = 0;
        m_hasArrivedAtStart = false;
        
        // 确保司机重新注册到派单系统，以便接收新订单
        if (m_driver->isonline()) {
            DispatchSystem::instance()->registerdriver(m_driver);
        }
        
        // 更新地图标记
        updatemapmarkers();
    }
}

void DriverWindow::onorderassigned(Order *order)
{
    // 如果订单为空，直接返回
    if (!order) {
        return;
    }
    
    // 检查司机是否已经有订单在处理
    if (m_driver->hasactiveorder()) {
        return; // 已经有活跃订单，拒绝新订单
    }
    
    // 检查是否已经处理过该订单，避免重复弹窗
    if (m_currentOrder && m_currentOrder == order) {
        return; // 已经处理过该订单，拒绝重复处理
    }
    
    // 清除旧的订单和路线
    m_currentOrder = nullptr;
    m_currentPath.clear();
    m_currentPathIndex = 0;
    m_hasArrivedAtStart = false;
    
    // 设置新订单
    m_currentOrder = order;
    updateorderinfo(order);
    
    ui->acceptOrderBtn->setEnabled(true);
    ui->rejectOrderBtn->setEnabled(true);
    
    // 更新地图标记，清除旧路线
    updatemapmarkers();
    
    // 绘制路线预览，让司机能看到路线、距离和时长
    if (order) {
        QPair<int, int> driverPos = m_driver->currentlocation();
        QPair<int, int> startPos = order->startlocation();
        QPair<int, int> endPos = order->endlocation();
        
        // 先规划司机到乘客起点的路径
        QList<QPair<int, int>> path1 = PathPlanner::instance()->planpath(driverPos.first, driverPos.second, startPos.first, startPos.second);
        // 再规划乘客起点到终点的路径
        QList<QPair<int, int>> path2 = PathPlanner::instance()->planpath(startPos.first, startPos.second, endPos.first, endPos.second);
        
        // 合并路径用于预览
        QList<QPair<int, int>> previewPath = path1;
        previewPath.append(path2.mid(1));
        
        drawroute(previewPath);
    }
    
    QMessageBox::information(this, "新订单", "您有一个新订单，请及时处理！");
}

void DriverWindow::onorderstatuschanged(Order *order, int oldstatus, int newstatus)
{
    // 如果订单为空，直接返回
    if (!order) {
        return;
    }

    QString statusText;
    switch (newstatus) {
    case Order::Pending:
        statusText = "待派单";
        break;
    case Order::Accepted:
        statusText = "已接单";
        break;
    case Order::OnTheWay:
        statusText = "司机正在前往";
        break;
    case Order::PickingUp:
        statusText = "正在接驾";
        break;
    case Order::InProgress:
        statusText = "行程中";
        break;
    case Order::Completed: {
        statusText = "已完成";
        ui->startTripBtn->setEnabled(false);
        ui->endTripBtn->setEnabled(false);
        
        // 更新累计里程显示
        updatetotalmileage();
        
        // 只有当该订单是当前司机的订单时，才显示行程结束提示
        if (order->driver() == m_driver || order == m_currentOrder) {
            // 行程结束提示
            double income = order->driverincome();
            double fee = order->platformfee();
            QMessageBox::information(this, "行程结束", 
                QString("恭喜！您的行程已完成\n" 
                        "本次收入：¥%1\n" 
                        "平台抽成：¥%2\n" 
                        "实际收入：¥%3").arg(order->actualcost(), 0, 'f', 2).arg(fee, 0, 'f', 2).arg(income, 0, 'f', 2),
                QMessageBox::Ok);
        }
        break;
    }
    case Order::Cancelled:
        statusText = "已取消";
        ui->acceptOrderBtn->setEnabled(false);
        ui->rejectOrderBtn->setEnabled(false);
        ui->startTripBtn->setEnabled(false);
        ui->endTripBtn->setEnabled(false);
        break;
    default:
        statusText = "未知状态";
        break;
    }

    // 只有当订单是当前订单时，才更新订单信息和行程状态
    if (order == m_currentOrder) {
        // 更新订单信息
        updateorderinfo(order);
        
        // 更新行程状态
        ui->tripStatusLabel->setText(QString("行程状态：%1").arg(statusText));
    }
}

void DriverWindow::updatelocation()
{
    // 如果有当前订单和路径，按照路径移动
    if (m_currentOrder && !m_currentPath.isEmpty()) {
        // 按照路径移动
        if (m_currentPathIndex < m_currentPath.size()) {
            // 检查当前位置是否已经到达起点
            QPair<int, int> currentPos = m_driver->currentlocation();
            QPair<int, int> startPos = m_currentOrder->startlocation();
            QPair<int, int> nextPos = m_currentPath[m_currentPathIndex];
            
            // 如果已经到达起点，但行程尚未开始，则停止移动
            if (m_hasArrivedAtStart && m_currentOrder->status() != Order::InProgress) {
                return;
            }
            
            // 无论是否到达起点，都继续移动
            m_driver->setcurrentlocation(nextPos.first, nextPos.second);
            
            // 移动到下一个路径点
            m_currentPathIndex++;
            
            // 检查是否到达起点或终点
            checkarrivalstatus();
        }
    }
    
    // 更新地图上的司机位置
    updatemapmarkers();
}

void DriverWindow::updateorderinfo(Order *order)
{
    if (!order) {
        // 清空所有订单信息
        ui->orderIdLabel->setText("订单编号：无");
        ui->passengerInfoLabel->setText("乘客：无");
        ui->startLocationLabel->setText("起点：无");
        ui->endLocationLabel->setText("终点：无");
        ui->estimatedDistanceLabel->setText("预估距离：0.0 km");
        ui->estimatedTimeLabel->setText("预估时长：0.0 分钟");
        return;
    }
    
    ui->orderIdLabel->setText(QString("订单编号：%1").arg(order->id()));
    
    // 检查乘客是否为空，避免空指针异常
    QString passengerName = order->passenger() ? order->passenger()->name() : "未知乘客";
    ui->passengerInfoLabel->setText(QString("乘客：%1").arg(passengerName));
    
    QPair<int, int> startPos = order->startlocation();
    QPair<int, int> endPos = order->endlocation();
    
    ui->startLocationLabel->setText(QString("起点：(%1, %2)").arg(startPos.first).arg(startPos.second));
    ui->endLocationLabel->setText(QString("终点：(%1, %2)").arg(endPos.first).arg(endPos.second));
    
    // 重新计算距离和时长，使用与平台端相同的逻辑
    int segmentCount = abs(endPos.first - startPos.first) + abs(endPos.second - startPos.second);
    double distance = segmentCount * 3.0; // 每个网格单元代表3km
    double time = segmentCount * 1.5; // 每个网格单元代表1.5分钟
    
    ui->estimatedDistanceLabel->setText(QString("预估距离：%1 km").arg(distance, 0, 'f', 1));
    ui->estimatedTimeLabel->setText(QString("预估时长：%1 分钟").arg(time, 0, 'f', 1));
}

void DriverWindow::drawroute(const QList<QPair<int, int>> &path)
{
    if (!m_scene || path.isEmpty()) {
        return;
    }

    // 清除旧的路径和标记
    QList<QGraphicsItem *> items = m_scene->items();
    for (QGraphicsItem *item : items) {
        if (item->data(0).toString() == "route" || item->data(0).toString() == "start" || item->data(0).toString() == "end") {
            m_scene->removeItem(item);
            delete item;
        }
    }

    // 清除路线列表（不再重复删除，因为已经在上面的循环中处理了）
    m_routeLines.clear();

    // 绘制路径
    QPen routePen(Qt::blue, 5); // 增加线条宽度，确保可见
    routePen.setStyle(Qt::SolidLine);
    routePen.setCapStyle(Qt::RoundCap);
    routePen.setJoinStyle(Qt::RoundJoin);
    
    for (int i = 0; i < path.size() - 1; ++i) {
        // 直接使用网格坐标转换为屏幕坐标
        QPointF startPos = maptoscreen(path[i]);
        QPointF endPos = maptoscreen(path[i+1]);
        
        QGraphicsLineItem *line = m_scene->addLine(startPos.x(), startPos.y(), endPos.x(), endPos.y(), routePen);
        line->setData(0, "route");
        line->setZValue(1); // 确保路线显示在最上层
        m_routeLines.append(line); // 将线条添加到m_routeLines列表中，便于管理
    }

    // 标记起点和终点
    QPointF startScreenPos = maptoscreen(path.first());
    QPointF endScreenPos = maptoscreen(path.last());

    // 起点（绿色）
    QGraphicsEllipseItem *startItem = new QGraphicsEllipseItem(startScreenPos.x() - 8, startScreenPos.y() - 8, 16, 16);
    startItem->setPen(QPen(Qt::green, 2));
    startItem->setBrush(QBrush(Qt::green));
    startItem->setData(0, "start");
    startItem->setZValue(2); // 确保标记显示在路线之上
    m_scene->addItem(startItem);

    // 终点（红色）
    QGraphicsEllipseItem *endItem = new QGraphicsEllipseItem(endScreenPos.x() - 8, endScreenPos.y() - 8, 16, 16);
    endItem->setPen(QPen(Qt::red, 2));
    endItem->setBrush(QBrush(Qt::red));
    endItem->setData(0, "end");
    endItem->setZValue(2); // 确保标记显示在路线之上
    m_scene->addItem(endItem);
    
    // 确保场景更新
    m_scene->update();
}

void DriverWindow::redrawcurrentroute()
{
    // 如果有当前路径，重新绘制路线
    if (!m_currentPath.isEmpty()) {
        drawroute(m_currentPath);
    }
}

void DriverWindow::startdrivermovement()
{
    // 如果已经有路径，不需要重新规划
    if (m_currentPath.isEmpty() && m_currentOrder) {
        QPair<int, int> driverPos = m_driver->currentlocation();
        QPair<int, int> startPos = m_currentOrder->startlocation();
        QPair<int, int> endPos = m_currentOrder->endlocation();
        
        // 先规划司机到乘客起点的路径
        QList<QPair<int, int>> path1 = PathPlanner::instance()->planpath(driverPos.first, driverPos.second, startPos.first, startPos.second);
        // 再规划乘客起点到终点的路径
        QList<QPair<int, int>> path2 = PathPlanner::instance()->planpath(startPos.first, startPos.second, endPos.first, endPos.second);
        
        // 合并路径
        m_currentPath = path1;
        m_currentPath.append(path2.mid(1));
        m_currentPathIndex = 0;
        m_hasArrivedAtStart = false;
        
        drawroute(m_currentPath);
    }
    
    // 确保位置更新定时器正在运行
    if (!m_locationTimer->isActive()) {
        m_locationTimer->start(1000);
    }
}

void DriverWindow::checkarrivalstatus()
{
    if (!m_currentOrder || m_currentPath.isEmpty()) {
        return;
    }
    
    QPair<int, int> currentPos = m_driver->currentlocation();
    QPair<int, int> startPos = m_currentOrder->startlocation();
    QPair<int, int> endPos = m_currentOrder->endlocation();
    
    // 检查是否到达起点
    if (!m_hasArrivedAtStart) {
        // 检查是否到达起点，允许一定的误差
        if (currentPos.first == startPos.first && currentPos.second == startPos.second) {
            m_hasArrivedAtStart = true;
            
            // 更新UI状态
            ui->startTripBtn->setEnabled(true); // 到达起点后允许开始行程
            ui->tripStatusLabel->setText("行程状态：已到达起点，可开始行程");
            
            // 重新绘制路线，确保路线显示正确
            drawroute(m_currentPath);
        }
    } 
    // 检查是否到达终点
    else {
        // 检查是否到达终点，允许一定的误差
        if (currentPos.first == endPos.first && currentPos.second == endPos.second) {
            ui->endTripBtn->setEnabled(true); // 到达终点后允许结束行程
            ui->tripStatusLabel->setText("行程状态：已到达终点，可结束行程");
        }
    }
}

void DriverWindow::updatestatus()
{
    // 更新司机状态
    QString statusText;
    switch (m_driver->status()) {
    case User::Offline:
        statusText = "离线";
        break;
    case User::Online:
        statusText = "在线";
        break;
    case User::Busy:
        statusText = "忙碌";
        break;
    }
    ui->statusLabel->setText(QString("当前状态：%1").arg(statusText));
}

void DriverWindow::updatetotalmileage()
{
    // 更新累计里程显示
    ui->drivenDistanceLabel->setText(QString("累计里程：%1 km").arg(m_driver->totalmileage(), 0, 'f', 1));
}

void DriverWindow::updateavailableorders()
{
    // 检查司机是否已经有活跃订单
    if (m_driver->hasactiveorder()) {
        ui->acceptOrderBtn->setEnabled(false);
        ui->rejectOrderBtn->setEnabled(false);
        return;
    }
    
    // 如果当前已经有派单系统分配的订单，不要清除它
    if (m_currentOrder) {
        // 保持当前订单和操作按钮状态不变
        return;
    }
    
    // 只更新UI状态，让司机等待派单系统的分配
    ui->acceptOrderBtn->setEnabled(false);
    ui->rejectOrderBtn->setEnabled(false);
    
    // 清除当前订单信息
    m_currentOrder = nullptr;
    updateorderinfo(nullptr);
    
    // 更新地图标记，清除旧路线
    updatemapmarkers();
}

void DriverWindow::onavailableordersupdated()
{
    // 当可用订单更新时，更新地图标记和可用订单
    updatemapmarkers();
    updateavailableorders();
}

void DriverWindow::clearmaproutes()
{
    // 清除所有路线线条
    QList<QGraphicsItem *> items = m_scene->items();
    for (QGraphicsItem *item : items) {
        // 删除标记为路线的图形项
        if (item->data(0).toString() == "route" || 
            item->data(0).toString() == "start" || 
            item->data(0).toString() == "end") {
            m_scene->removeItem(item);
            delete item;
        }
    }
    
    // 清除路线列表（不再重复删除，因为已经在上面的循环中处理了）
    m_routeLines.clear();
}
