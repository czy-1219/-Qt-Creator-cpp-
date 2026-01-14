#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "driver.h"
#include "passenger.h"
#include <QMainWindow>
#include <QList>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createusers();
private slots:
    void onpassengerbtnclicked();
    void ondriverbtnclicked();
    void onplatformbtnclicked();
    void onregisterpassengerbtnclicked();
    void on_registerdriverbtn_clicked();



private:
    void cleanupactiveorders();
    Ui::MainWindow *ui;
    
    // 保存用户数据
    void saveuserdata();
    // 加载用户数据
    void loaduserdata();
    
    // 用户数据存储
    QList<Passenger*> m_passengers;
    QList<Driver*> m_drivers;
};
#endif // MAINWINDOW_H
