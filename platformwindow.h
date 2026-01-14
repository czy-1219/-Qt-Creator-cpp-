#ifndef PLATFORMWINDOW_H
#define PLATFORMWINDOW_H

#include <QMainWindow>
#include <QTimer>//定时器

class Driver;
class Order;

namespace Ui {
class PlatformWindow;
}

class PlatformWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlatformWindow(QWidget *parent = nullptr);
    ~PlatformWindow();

private slots:
    void updatedashboard();
    void onordercreated(Order *order);
    void onorderstatuschanged(Order *order, int oldstatus, int newstatus);
    void ondriverstatuschanged (Driver *driver);

private:
    Ui::PlatformWindow *ui;
    QTimer *m_updateTimer;
    
    void updateorderlist();
    void updatedriverlist();
    void updatemap();
    void updatestats();
};

#endif // PLATFORMWINDOW_H
