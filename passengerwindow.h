#ifndef PASSENGERWINDOW_H
#define PASSENGERWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>//继承自 QObject
#include<QGraphicsEllipseItem>//Qt Graphics View 框架中 椭圆 / 圆形图形项（
class Passenger;
class Order;

namespace Ui {
class PassengerWindow;
}

class PassengerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PassengerWindow(Passenger *passenger, QWidget *parent = nullptr);
    ~PassengerWindow();
    
    // 事件过滤器，用于处理地图点击事件
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_requestRideBtn_clicked();
    void on_cancelOrderBtn_clicked();
    void on_orderstatuschanged(Order *order, int oldstatus, int newstatus);
    void updatedriverlocation(int x, int y);
    void updatetripprogress(double progress);
    void oncartypechanged(int index);
    void updatedriverposition();

private:
    Ui::PassengerWindow *ui;
    Passenger *m_passenger;
    Order *m_currentOrder;
    
    // 地图相关成员变量
    QGraphicsScene *m_scene;
    bool m_startPointSet;
    bool m_endPointSet;
    QPair<int, int> m_startPoint;
    QPair<int, int> m_endPoint;
    QGraphicsEllipseItem *m_startMarker;
    QGraphicsEllipseItem *m_endMarker;
    QGraphicsTextItem *m_startText;
    QGraphicsTextItem *m_endText;
    QGraphicsEllipseItem *m_driverMarker;
    QGraphicsTextItem *m_driverText;
    // 定时器
    QTimer *m_updateTimer;
    // 地图绘制
    void drawgridmap();
    void updatemapmarkers();
    
    // 坐标转换函数（简化坐标）
    QPair<int, int> screentomap(const QPointF &screenPos);
    QPointF maptoscreen(const QPair<int, int> &mapPos);
    
    void updateorderinfo(Order *order);
    void drawroute(const QList<QPair<int, int>> &path);
    void updateestimatedinfo(double distance, double time, double cost);
};

#endif // PASSENGERWINDOW_H
