#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QList>
#include "passenger.h"
#include "driver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    enum UserType {
        PassengerType,
        DriverType
    };

    explicit LoginWindow(UserType userType, QWidget *parent = nullptr);
    ~LoginWindow();

    void setpassengers(const QList<Passenger*> &passengers);
    void setdrivers(const QList<Driver*> &drivers);
    
    Passenger* selectedpassenger() const;
    Driver* selecteddriver() const;

private slots:
    void on_loginBtn_clicked();
    void on_cancelBtn_clicked();

private:
    Ui::LoginWindow *ui;
    
    UserType m_userType;
    QList<Passenger*> m_passengers;
    QList<Driver*> m_drivers;
    
    Passenger* m_selectedPassenger;
    Driver* m_selectedDriver;
    
    void setupui();
    void populateuserlist();
};

#endif // LOGINWINDOW_H