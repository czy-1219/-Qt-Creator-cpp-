#include "passengerwindow.h"
#include "ui_passengerwindow.h"
#include "passenger.h"
#include "order.h"
#include "ordermanager.h"
#include "pathplanner.h"
#include  "driver.h"
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include <QMessageBox>//弹窗
#include <QMouseEvent>// Qt鼠标事件类，处理鼠标点击、移动等事件
#include<QTimer>
//  QPointF Qt 提供的一个专门用来表示「二维浮点型坐标点」的封装类
PassengerWindow::PassengerWindow(Passenger *passenger, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PassengerWindow)
    , m_passenger(passenger)
    , m_currentOrder(nullptr)
    , m_startPointSet(false)
    , m_endPointSet(false)
    , m_driverMarker(nullptr)
    , m_driverText(nullptr)
    , m_updateTimer(new QTimer(this))
{
    ui->setupUi(this);

    // 设置初始状态
    ui->cancelOrderBtn->setEnabled(false);
    ui->tripProgressBar->setValue(0);
    // 更新用户信息标签，显示实际的乘客账号信息
    ui->userInfoLabel->setText(QString("乘客：%1 (%2)").arg(m_passenger->name()).arg(m_passenger->id()));
    
    // 初始化地图场景
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->mapView->setScene(scene);
    ui->mapView->setSceneRect(0, 0, 700, 500);
    //画布
    // 保存场景指针
    m_scene = scene;
    // 绘制简单的网格地图
    drawgridmap();
    
    // 添加地图点击事件
    ui->mapView->viewport()->installEventFilter(this);

    // 连接信号槽
    connect(m_passenger, &Passenger::riderequested, this, [this](int startX, int startY, int endX, int endY, const QString &carType) {
        // 创建订单
        Order *order = OrderManager::instance()->createorder(m_passenger, startX, startY, endX, endY, carType);
        m_currentOrder = order;
        
        // 更新订单信息
        updateorderinfo(order);
        // 规划路径
        QList<QPair<int, int>> path = PathPlanner::instance()->planpath(startX, startY, endX, endY);
        drawroute(path);
        // 使用订单的实际预估信息
        updateestimatedinfo(order->estimateddistance(), order->estimatedtime(), order->estimatedcost());
        // 启用取消按钮
        ui->cancelOrderBtn->setEnabled(true);
    });
    
    // 连接订单状态变化信号
    connect(OrderManager::instance(), &OrderManager::orderstatuschanged, this, &PassengerWindow::on_orderstatuschanged);
    
    // 连接车型选择变化信号
    connect(ui->carTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PassengerWindow::oncartypechanged);
    
    // 连接定时器信号，定期更新司机位置
    connect(m_updateTimer, &QTimer::timeout, this, &PassengerWindow::updatedriverposition);
    // 初始化预估信息
    oncartypechanged(0);
}

PassengerWindow::~PassengerWindow()
{
    delete ui;
}

void PassengerWindow::drawgridmap()
{
    // 清除现有内容
    m_scene->clear();
    
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
    
    // 绘制网格坐标标签
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
    m_startMarker = nullptr;
    m_endMarker = nullptr;
    m_startText = nullptr;
    m_endText = nullptr;
    m_startPointSet = false;
    m_endPointSet = false;
    updatemapmarkers();
}

QPair<int, int> PassengerWindow::screentomap(const QPointF &screenPos)
{
    // 简化坐标转换：将屏幕坐标转换为网格坐标
    int gridSize = 50;
    int gridX = qRound(screenPos.x() / gridSize);
    int gridY = qRound(screenPos.y() / gridSize);
    
    return qMakePair(gridX, gridY);
}

QPointF PassengerWindow::maptoscreen(const QPair<int, int> &mapPos)
{
    // 简化坐标转换：将网格坐标转换为屏幕坐标
    int gridSize = 50;
    int gridX = mapPos.first;
    int gridY = mapPos.second;
    
    return QPointF(gridX * gridSize, gridY * gridSize);
}

void PassengerWindow::updatemapmarkers()
{
    // 移除旧标记
    if (m_startMarker) {
        m_scene->removeItem(m_startMarker);
        delete m_startMarker;
        m_startMarker = nullptr;
    }
    if (m_endMarker) {
        m_scene->removeItem(m_endMarker);
        delete m_endMarker;
        m_endMarker = nullptr;
    }
    
    // 移除旧文字标记
    if (m_startText) {
        m_scene->removeItem(m_startText);
        delete m_startText;
        m_startText = nullptr;
    }
    if (m_endText) {
        m_scene->removeItem(m_endText);
        delete m_endText;
        m_endText = nullptr;
    }
    
    // 绘制起点标记
    if (m_startPointSet) {
        QPointF pos = maptoscreen(m_startPoint);
        m_startMarker = m_scene->addEllipse(pos.x() - 10, pos.y() - 10, 20, 20, QPen(Qt::green), QBrush(Qt::green));
        m_startText = m_scene->addText("起点");
        m_startText->setPos(pos.x() - 15, pos.y() - 30);
    }
    
    // 绘制终点标记
    if (m_endPointSet) {
        QPointF pos = maptoscreen(m_endPoint);
        m_endMarker = m_scene->addEllipse(pos.x() - 10, pos.y() - 10, 20, 20, QPen(Qt::red), QBrush(Qt::red));
        m_endText = m_scene->addText("终点");
        m_endText->setPos(pos.x() - 15, pos.y() - 30);
    }
}

bool PassengerWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->mapView->viewport() && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            // 获取点击位置
            QPointF scenePos = ui->mapView->mapToScene(mouseEvent->pos());
            QPair<int, int> mapPos = screentomap(scenePos);
            
            // 简化坐标显示（网格坐标）
            int gridX = mapPos.first;
            int gridY = mapPos.second;
            QString coordText = QString("%1,%2").arg(gridX).arg(gridY);
            
            // 设置起点或终点
            if (!m_startPointSet) {
                // 设置起点
                m_startPoint = mapPos;
                m_startPointSet = true;
                ui->startLocationEdit->setText(coordText);
            } else if (!m_endPointSet) {
                // 设置终点
                m_endPoint = mapPos;
                m_endPointSet = true;
                ui->endLocationEdit->setText(coordText);
            } else {
                // 重置，重新设置起点
                m_startPoint = mapPos;
                m_startPointSet = true;
                m_endPointSet = false;
                ui->startLocationEdit->setText(coordText);
                ui->endLocationEdit->clear();
            }
            
            // 更新地图标记
            updatemapmarkers();
            
            // 如果起点和终点都已设置，更新预估信息
            if (m_startPointSet && m_endPointSet) {
                oncartypechanged(ui->carTypeCombo->currentIndex());
            }
            
            return true;
        }
    }
    
    return QMainWindow::eventFilter(obj, event);
}

void PassengerWindow::on_requestRideBtn_clicked()
{
    // 检查是否已有订单
    if (m_currentOrder) {
        QMessageBox::warning(this, "错误", "您当前已有订单，请先取消或完成当前订单再继续叫车");
        return;
    }
    
    // 检查起点和终点是否设置
    if (!m_startPointSet || !m_endPointSet) {
        QMessageBox::warning(this, "错误", "请先点击地图设置起点和终点");
        return;
    }
    
    QString carType = ui->carTypeCombo->currentText();
    
    // 发起叫车请求
            m_passenger->requestride(m_startPoint.first, m_startPoint.second, m_endPoint.first, m_endPoint.second, carType);
}

void PassengerWindow::on_cancelOrderBtn_clicked()
{
    if (m_currentOrder) {
        // 只调用OrderManager的cancelorder方法，避免重复删除
        OrderManager::instance()->cancelorder(m_currentOrder);
        
        // 更新界面
        ui->orderIdLabel->setText("订单编号：");
        ui->statusLabel->setText("状态：待派单");

        ui->cancelOrderBtn->setEnabled(false);
        
        // 清空地图上的标记和路径
        updatemapmarkers();
        
        // 清除地图上的路线
        QGraphicsScene *scene = ui->mapView->scene();
        if (scene) {
            QList<QGraphicsItem *> items = scene->items();
            for (QGraphicsItem *item : items) {
                // 只删除路线和标记，不删除网格线和坐标文本
                if (item->data(0).toString() == "route" || item->data(0).toString() == "driver") {
                    scene->removeItem(item);
                    delete item;
                }
            }
        }
        
        m_currentOrder = nullptr;
    }
}

void PassengerWindow::on_orderstatuschanged(Order *order, int oldstatus, int newstatus)
{
    if (order != m_currentOrder) {
        return;
    }

    // 根据订单状态执行不同操作
    switch (newstatus) {
    case Order::Accepted:
        // 订单被接单后，启动定时器更新司机位置
        m_updateTimer->start(1000);
        break;
    case Order::Completed: {
        ui->cancelOrderBtn->setEnabled(false);
        // 行程完成后，停止定时器
        m_updateTimer->stop();
        
        // 行程结束提示
        double cost = order->actualcost();
        QMessageBox::information(this, "行程结束", 
            QString("您的行程已完成\n" 
                    "本次行程费用：¥%1\n" 
                    "感谢您的使用！").arg(cost, 0, 'f', 2),
            QMessageBox::Ok);
        
        // 清除当前订单指针
        m_currentOrder = nullptr;
        break;
    }
    case Order::Cancelled:
        ui->cancelOrderBtn->setEnabled(false);
        // 订单取消后，停止定时器
        m_updateTimer->stop();
        
        // 清除当前订单指针
        m_currentOrder = nullptr;
        break;
    default:
        break;
    }

    // 更新完整的订单信息
        updateorderinfo(order);
//优化显示
    ui->statusLabel->setStyleSheet("font-weight: bold; font-size: 14px; color: #0078d7;");
}

void PassengerWindow::updatedriverposition()
{
    // 检查当前订单是否存在
    if (!m_currentOrder) {
        return;
    }
    
    // 检查订单是否有司机
    Driver *driver = m_currentOrder->driver();
    if (!driver) {
        return;
    }
    
    // 获取司机的当前位置
    QPair<int, int> driverPos = driver->currentlocation();
    
    // 清除旧的司机位置标记
    if (m_driverMarker) {
        m_scene->removeItem(m_driverMarker);
        delete m_driverMarker;
        m_driverMarker = nullptr;
    }
    
    if (m_driverText) {
        m_scene->removeItem(m_driverText);
        delete m_driverText;
        m_driverText = nullptr;
    }
    
    // 使用正确的坐标转换
    QPointF screenPos = maptoscreen(driverPos);
    
    // 添加新的司机位置标记
    m_driverMarker = m_scene->addEllipse(screenPos.x() - 8, screenPos.y() - 8, 16, 16, QPen(Qt::blue), QBrush(Qt::blue));
    m_driverText = m_scene->addText("司机");
    m_driverText->setPos(screenPos.x() - 15, screenPos.y() - 30);
    m_driverText->setDefaultTextColor(Qt::blue);
}

void PassengerWindow::updatedriverlocation(int x, int y)
{
    // 模拟更新司机位置
    QGraphicsScene *scene = ui->mapView->scene();
    if (!scene) {
        return;
    }

    // 清除旧的司机位置标记
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        if (item->data(0).toString() == "driver") {
            scene->removeItem(item);
            delete item;
        }
    }

    // 使用正确的坐标转换
    QPointF screenPos = maptoscreen(qMakePair(x, y));
    
    // 添加新的司机位置标记
    QGraphicsEllipseItem *driverItem = new QGraphicsEllipseItem(screenPos.x() - 5, screenPos.y() - 5, 10, 10);
    driverItem->setPen(QPen(Qt::red, 2));
    driverItem->setBrush(QBrush(Qt::red));
    driverItem->setData(0, "driver");
    scene->addItem(driverItem);
}

void PassengerWindow::updatetripprogress(double progress)
{
   ui->tripProgressBar->setValue(static_cast<int>(progress * 100));
}

void PassengerWindow::oncartypechanged(int index)
{
    int segmentCount = 0;
    
    // 如果起点和终点都设置了，使用实际的线段数
    if (m_startPointSet && m_endPointSet) {
        // 解析起点和终点坐标
        QString startText = ui->startLocationEdit->text();
        QString endText = ui->endLocationEdit->text();
        
        QStringList startParts = startText.split(",");
        QStringList endParts = endText.split(",");
        
        if (startParts.size() == 2 && endParts.size() == 2) {
            int startX = startParts[0].toInt();
            int startY = startParts[1].toInt();
            int endX = endParts[0].toInt();
            int endY = endParts[1].toInt();
            
            // 计算线段数（曼哈顿距离）
            segmentCount = abs(endX - startX) + abs(endY - startY);
        }
    } else {
        // 否则使用默认值
        segmentCount = 0;
    }
    double distance = segmentCount * 3.0; // 每3km
    double baseTime = segmentCount * 1.5; // 每个网格单元1.5分钟
    double baseCost = segmentCount * 3.0; //每段3元
    // 根据车型调整
    QString carType = ui->carTypeCombo->currentText();
    double adjustedTime = baseTime;
    double adjustedCost = baseCost;
    
    if (carType == "专车") {
        // 专车：单价上浮20%，时间缩短10%
        adjustedTime = baseTime * 0.9;
        adjustedCost = baseCost * 1.2;
    }
    // 更新预估信息
        updateestimatedinfo(distance, adjustedTime, adjustedCost);
}

void PassengerWindow::updateorderinfo(Order *order)
{
    if (!order) {
        // 清空所有订单信息
        ui->orderIdLabel->setText("订单编号：无");
        ui->statusLabel->setText("行程状态：无订单");
        return;
    }
    
    // 显示订单编号
    ui->orderIdLabel->setText(QString("订单编号：%1").arg(order->id()));
    
    // 获取订单状态文本
    QString statusText;
    switch (order->status()) {
    case Order::Pending:
        statusText = "待派单";
        break;
    case Order::Accepted:
        statusText = "已接单，前往起点中";
        break;
    case Order::OnTheWay:
        statusText = "司机正在前往起点";
        break;
    case Order::PickingUp:
        statusText = "正在前往起点";
        break;
    case Order::InProgress:
        statusText = "行程进行中";
        break;
    case Order::Completed:
        statusText = "行程已完成";
        break;
    case Order::Cancelled:
        statusText = "订单已取消";
        break;
    default:
        statusText = "未知状态";
        break;
    }
    
    // 更新状态标签
    ui->statusLabel->setText(QString("行程状态：%1").arg(statusText));
    
    // 更新预估信息
        updateestimatedinfo(order->estimateddistance(), order->estimatedtime(), order->estimatedcost());
    
    // 显示司机信息（如果有）
    Driver *driver = order->driver();
    if (driver) {
        // 在地图组中显示司机信息
        QString driverInfo = QString("司机：%1\n车牌号：%2\n车型：%3").arg(driver->name()).arg(driver->licenseplate()).arg(driver->carmodel());
        QList<QLabel *> driverLabels = ui->mapGroup->findChildren<QLabel *>();
        if (!driverLabels.isEmpty()) {
            // 如果已有司机信息标签，更新它
            driverLabels.first()->setText(driverInfo);
        } else {
            // 如果没有司机信息标签，创建一个
            QLabel *driverLabel = new QLabel(driverInfo);
            driverLabel->setWordWrap(true);
            ui->mapGroup->layout()->addWidget(driverLabel);
        }
    } else {
        // 清除司机信息
        QList<QLabel *> driverLabels = ui->mapGroup->findChildren<QLabel *>();
        for (QLabel *label : driverLabels) {
            delete label;
        }
    }
}

void PassengerWindow::drawroute(const QList<QPair<int, int>> &path)
{
    QGraphicsScene *scene = ui->mapView->scene();
    if (!scene || path.isEmpty()) {
        return;
    }
    // 清除旧的路径
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        if (item->data(0).toString() == "route" || item->data(0).toString() == "start" || item->data(0).toString() == "end") {
            scene->removeItem(item);
            delete item;
        }
    }

    // 绘制路径
    QPen routePen(Qt::blue, 3);
    for (int i = 0; i < path.size() - 1; ++i) {
        double x1 = path[i].first * 50; // 网格X转屏幕x坐标
        double y1 = path[i].second * 50; // 网格Y转屏幕y坐标
        double x2 = path[i+1].first * 50;
        double y2 = path[i+1].second * 50;
        
        QGraphicsLineItem *line = scene->addLine(x1, y1, x2, y2, routePen);
        line->setData(0, "route");
    }
    // 标记起点和终点
    double startX = path.first().first * 50;
    double startY = path.first().second * 50;
    double endX = path.last().first * 50;
    double endY = path.last().second * 50;
    // 起点（
    QGraphicsEllipseItem *startItem = new QGraphicsEllipseItem(startX - 8, startY - 8, 16, 16);
    startItem->setPen(QPen(Qt::green, 2));
    startItem->setBrush(QBrush(Qt::green));
    startItem->setData(0, "start");
    scene->addItem(startItem);
    // 终点
    QGraphicsEllipseItem *endItem = new QGraphicsEllipseItem(endX - 8, endY - 8, 16, 16);
    endItem->setPen(QPen(Qt::red, 2));
    endItem->setBrush(QBrush(Qt::red));
    endItem->setData(0, "end");
    scene->addItem(endItem);
}

void PassengerWindow::updateestimatedinfo(double distance, double time, double cost)
{
    ui->distanceLabel->setText(QString("距离：%1 km").arg(distance));
    ui->timeLabel->setText(QString("时长：%1 分钟").arg(time));
    ui->costLabel->setText(QString("费用：¥%2").arg(cost));
}
