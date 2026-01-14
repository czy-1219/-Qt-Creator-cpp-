#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "passengerwindow.h"
#include "driverwindow.h"
#include "platformwindow.h"
#include "passenger.h"
#include"order.h"
#include "dispatchsystem.h"
#include "driver.h"
#include "ordermanager.h"
#include "mapdata.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QInputDialog>
/*JSON 本身是通用的数据交换格式，
 解决跨平台、跨系统、跨服务的数据交互问题
类型安全，自动处理格式问题，不会中文乱码

qt的单例类在程序运行中只允许一个建立对象，不存在第二个对象
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        // 生成网格地图
        MapData::instance()->generategridmap(50, 50, 50);
//类名 *对象指针 = 类名::instance() 在单例类才能用
        // 连接按钮点击事件
        //connect(发送者指针, &发送者类名::信号函数名, 接收者指针, &接收者类名::槽函数名);
        connect(ui->passengerBtn, &QPushButton::clicked, this, &MainWindow::onpassengerbtnclicked);
        connect(ui->driverBtn, &QPushButton::clicked, this, &MainWindow::ondriverbtnclicked);
        connect(ui->platformBtn, &QPushButton::clicked, this, &MainWindow::onplatformbtnclicked);
        connect(ui->registerPassengerBtn, &QPushButton::clicked, this, &MainWindow::onregisterpassengerbtnclicked);
        connect(ui->registerDriverBtn, &QPushButton::clicked, this, &MainWindow::on_registerdriverbtn_clicked);
        // 加载用户数据
        loaduserdata();
}

MainWindow::~MainWindow()
{
    // 清理所有活跃订单和路线状态
    cleanupactiveorders();
    // 保存用户数据
    saveuserdata();
    // 清理资源
    qDeleteAll(m_passengers);
    qDeleteAll(m_drivers);//自带的清理函数
    delete ui;
}

void MainWindow::cleanupactiveorders()
{
    // 清理所有未完成的订单
    OrderManager *orderManager = OrderManager::instance();
    // 取消所有未完成的订单
    QList<Order *> activeOrders;
    activeOrders.append(orderManager->ordersbystatus(Order::Pending));
    activeOrders.append(orderManager->ordersbystatus(Order::Accepted));
    activeOrders.append(orderManager->ordersbystatus(Order::OnTheWay));
    activeOrders.append(orderManager->ordersbystatus(Order::PickingUp));
    activeOrders.append(orderManager->ordersbystatus(Order::InProgress));
    
    for (Order *order : activeOrders) {
        // 将未完成的订单状态重置为Pending
            if (order->status() != Order::Completed && order->status() != Order::Cancelled) {
                orderManager->updateorderstatus(order, Order::Pending);
                // 清除司机的分配
                order->setdriver(nullptr);
            }
    }
    // 清理派单系统中的活跃司机状态
    DispatchSystem *dispatchSystem = DispatchSystem::instance();
    for (Driver *driver : m_drivers) {
        // 如果司机在线，先下线
        if (driver->isonline()) {
            dispatchSystem->unregisterdriver(driver);
            driver->setonline(false);
        }
        
        // 清除司机的活跃订单状态
        if (driver->hasactiveorder()) {
            driver->clearactiveorder();
        }
    }
}

void MainWindow::saveuserdata()
{
    QJsonObject root;//创建一个空的的 JSON 对象
    
    // 保存乘客数据
    QJsonArray passengersArray;
    for (Passenger *passenger : m_passengers) {
        QJsonObject passengerObj;
        passengerObj["id"] = passenger->id();
        passengerObj["name"] = passenger->name();
        passengersArray.append(passengerObj);
    }
    root["passengers"] = passengersArray;
    
    // 保存司机数据
    QJsonArray driversArray;
    for (Driver *driver : m_drivers) {
        QJsonObject driverObj;
        driverObj["id"] = driver->id();
        driverObj["name"] = driver->name();
        driverObj["licensePlate"] = driver->licenseplate();
        driverObj["carModel"] = driver->carmodel();
        driverObj["gridX"] = driver->currentlocation().first;
        driverObj["gridY"] = driver->currentlocation().second;
        driverObj["completedOrders"] = driver->completedorders();
        driversArray.append(driverObj);
    }
    root["drivers"] = driversArray;
    

    
    // 写入文件
    QFile file("user_data.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonDocument doc(root);
        file.write(doc.toJson());
        file.close();
    }
}

void MainWindow::loaduserdata()
{
    // 读取文件
    QFile file("user_data.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // 文件不存在，创建默认
        createusers();
        return;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());//读取信息解析为QJsonDocument对象
    file.close();
    
    QJsonObject root = doc.object();//doc.object() 提取顶层json对象
    
    // 加载乘客数据
    QJsonArray passengersArray = root["passengers"].toArray();
    for (const QJsonValue &value : passengersArray) {
        QJsonObject passengerObj = value.toObject();
        Passenger *passenger = new Passenger(this);
        passenger->setid(passengerObj["id"].toString());
        passenger->setname(passengerObj["name"].toString());
        m_passengers.append(passenger);
    }
    
    // 加载司机数据
    QJsonArray driversArray = root["drivers"].toArray();
    for (const QJsonValue &value : driversArray) {
        QJsonObject driverObj = value.toObject();
        Driver *driver = new Driver(this);
        driver->setid(driverObj["id"].toString());
        driver->setname(driverObj["name"].toString());
        driver->setlicenseplate(driverObj["licensePlate"].toString());
        driver->setcarmodel(driverObj["carModel"].toString());
        int gridX = driverObj.contains("gridX") ? driverObj["gridX"].toInt() : 0;
        int gridY = driverObj.contains("gridY") ? driverObj["gridY"].toInt() : 0;
        driver->setcurrentlocation(gridX, gridY);
        driver->setcompletedorders(driverObj["completedOrders"].toInt());
        m_drivers.append(driver);
    }
    
    // 如果没有用户，创建默认用户
    if (m_passengers.isEmpty() || m_drivers.isEmpty()) {
        createusers();
    }
    
//JSON 规范定义了 6 种基础值类型：string（字符串）、number（数字）、boolean（布尔）、
//array（数组）、object（对象）、null（空值）
// QJsonValue的核心原理是用一个类封装所有这些类型,一旦创建，其内部存储的类型和数据就无法修改
}

void MainWindow::createusers()
{
    // 创建默认乘客
    Passenger *passenger = new Passenger(this);
    passenger->setid("PASS001");
    passenger->setname("张三");
    m_passengers.append(passenger);
    // 创建默认司机
    Driver *driver = new Driver(this);
    driver->setid(QString("DRIV001"));
    driver->setname(QString("司机1"));
    driver->setlicenseplate(QString("湘A12341"));
    driver->setcarmodel("大众朗逸");
    int gridX = 0;
    int gridY = 0;
    driver->setcurrentlocation(gridX, gridY);
    driver->setcompletedorders(120);
    m_drivers.append(driver);//等于pushback（）
}

void MainWindow::onregisterpassengerbtnclicked()
{
    // 注册新乘客
    QString name = QInputDialog::getText(this, "注册乘客", "请输入乘客姓名:");
    if (name.isEmpty()) {
        return;
    }
    QString id = QString("PASS%1").arg(m_passengers.size() + 1, 3, 10, QChar('0'));
    //.arg( 数字, 固定位数, 进制, 补位字符 )
    Passenger *passenger = new Passenger(this);
    passenger->setid(id);
    passenger->setname(name);
    m_passengers.append(passenger);
    
    QMessageBox::information(this, "注册成功", "乘客注册成功！");
};

void MainWindow::on_registerdriverbtn_clicked()
{
    // 注册新司机
    QString name = QInputDialog::getText(this, "注册司机", "请输入司机姓名:");//用于一键弹出对话款，输入输出同一条代码
    if (name.isEmpty()) {
        return;
    }
    
    QString licensePlate = QInputDialog::getText(this, "注册司机", "请输入车牌号:");
    if (licensePlate.isEmpty()) {
        return;
    }
    
    QString carModel = QInputDialog::getText(this, "注册司机", "请输入车型:");
    if (carModel.isEmpty()) {
        return;
    }
    
    // 生成唯一ID
    QString id = QString("DRIV%1").arg(m_drivers.size() + 1, 3, 10, QChar('0'));
    
    Driver *driver = new Driver(this);
    driver->setid(id);
    driver->setname(name);
    driver->setlicenseplate(licensePlate);
    driver->setcarmodel(carModel);
    int gridX = 0;
    int gridY = 0;
    driver->setcurrentlocation(gridX, gridY);
    driver->setcompletedorders(0);
    m_drivers.append(driver);
    
    QMessageBox::information(this, "注册成功", "司机注册成功！");
};

void MainWindow::onpassengerbtnclicked()
{
    if (m_passengers.isEmpty()) {
        onregisterpassengerbtnclicked();
    }
    
    if (m_passengers.isEmpty()) {
        return;
    }
    if (m_passengers.size() == 1) {
        Passenger *passenger = m_passengers.first();
        PassengerWindow *passengerWindow = new PassengerWindow(passenger, this);
        passengerWindow->show();
        return;
    }   
    // 多个乘客，显示选择列表
    QStringList passengerNames;
    for (Passenger *passenger : m_passengers) {
        passengerNames.append(QString("%1 (%2)").arg(passenger->name()).arg(passenger->id()));
    }
    
    bool ok;
    QString selectedName = QInputDialog::getItem(this, "选择乘客", "请选择您的乘客账号:", passengerNames, 0, false, &ok);
    /*弹出下拉框
     * static QString QInputDialog::getItem(
     QWidget *parent,       【可选】父窗口指针
  const QString &title,             【必填】标题栏
    const QString &label,           // 【必填】弹窗内的提示文字
    const QStringList &items,       // 【必填】下拉列表的所有选项，QStringList类型
    int currentIndex = 0,           // 【可选】默认选中的选项下标，从0开始，默认选第1项
    bool editable = true/false          // 【可选】下拉框是否允许手动输入内容
    bool *ok = nullptr,             // 【核心可选】输出型bool指针，判断用户是【确定】还是【取消】
    Qt::WindowFlags  flags = Qt::WindowFlags(),
    Qt::InputMethodHints inputMethodHints = Qt::ImhNone
);*/
    if (ok && !selectedName.isEmpty()) {
        // 找到选中的乘客
        for (Passenger *passenger : m_passengers) {
            QString displayName = QString("%1 (%2)").arg(passenger->name()).arg(passenger->id());
            if (displayName == selectedName) {
                // 打开乘客端界面
                PassengerWindow *passengerWindow = new PassengerWindow(passenger, this);
                passengerWindow->show();
                break;
            }
        }
    }
};

void MainWindow::ondriverbtnclicked()
{
    // 选择或创建司机
    if (m_drivers.isEmpty()) {
        on_registerdriverbtn_clicked();
    }
    
    if (m_drivers.isEmpty()) {
        return;
    }
    
    // 如果只有一个司机，直接使用
    if (m_drivers.size() == 1) {
        Driver *driver = m_drivers.first();
        DriverWindow *driverWindow = new DriverWindow(driver, this);
        driverWindow->show();
        return;
    }
    
    // 多个司机，显示选择列表
    QStringList driverNames;
    for (Driver *driver : m_drivers) {
        driverNames.append(QString("%1 (%2) | %3 %4").arg(driver->name()).arg(driver->id()).arg(driver->carmodel()).arg(driver->licenseplate()));
    }
    
    bool ok;
    QString selectedName = QInputDialog::getItem(this, "选择司机", "请选择您的司机账号:", driverNames, 0, false, &ok);
    
    if (ok && !selectedName.isEmpty()) {
        // 找到选中的司机
        for (Driver *driver : m_drivers) {
            QString displayName = QString("%1 (%2) | %3 %4").arg(driver->name()).arg(driver->id()).arg(driver->carmodel()).arg(driver->licenseplate());
            if (displayName == selectedName) {
                // 打开司机端界面
                DriverWindow *driverWindow = new DriverWindow(driver, this);
                driverWindow->show();
                break;
            }
        }
    }
};

void MainWindow::onplatformbtnclicked()
{
    PlatformWindow *platformWindow = new PlatformWindow(this);
    platformWindow->show(); // 打开平台监控端界面
};


