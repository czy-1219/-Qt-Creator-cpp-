#ifndef DRIVERWINDOW_H
#define DRIVERWINDOW_H

#include <QMainWindow>//Qt Widgets 模块的标准主窗口类
#include<QGraphicsScene>//图形项 配合QGraphicsView渲染
#include<QListWidgetItem>
class Driver;
class Order;

namespace Ui {
class DriverWindow;
}

class DriverWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DriverWindow(Driver *driver, QWidget *parent = nullptr);
    ~DriverWindow();
    
    // 事件过滤器，用于处理地图点击事件
    bool eventFilter(QObject *obj, QEvent *event) ;

private slots:
    void on_onlineBtn_clicked();
    void on_acceptOrderBtn_clicked();
    void on_rejectOrderBtn_clicked();
    void on_startTripBtn_clicked();
    void on_endTripBtn_clicked();
    void onorderassigned(Order *order);
    void onorderstatuschanged(Order *order, int oldstatus, int newstatus);
    void updatelocation();
    void onavailableordersupdated();
    void updateavailableorders();
    void clearmaproutes();
    void onotherdriveracceptedorder(Order *order);
private:
    Ui::DriverWindow *ui;
    Driver *m_driver;
    Order *m_currentOrder;
    QTimer *m_locationTimer;
    
    // 地图相关成员变量
    QGraphicsScene *m_scene;
    QGraphicsEllipseItem *m_driverMarker;
    QGraphicsTextItem *m_driverText;
    QList<QGraphicsEllipseItem*> m_passengerMarkers;
    QList<QGraphicsTextItem*> m_passengerTexts;
    QList<QGraphicsTextItem*> m_destinationTexts;
    QList<QGraphicsLineItem*> m_routeLines;
    
    // 路径相关成员变量
    QList<QPair<int, int>> m_currentPath;
    int m_currentPathIndex;
    bool m_hasArrivedAtStart;
    
    // 地图绘制函数
    void drawgridmap();
    void updatemapmarkers();
    
    // 坐标转换函数（简化坐标）
    QPair<int, int> screentomap(const QPointF &screenPos);
    QPointF maptoscreen(const QPair<int, int> &mapPos);
    
    void updateorderinfo(Order *order);
    void drawroute(const QList<QPair<int, int>> &path);
    void redrawcurrentroute();
    void updatestatus();
    void updatetotalmileage();
    void startdrivermovement();
    void checkarrivalstatus();
};

#endif // DRIVERWINDOW_H
