#ifndef USER_H
#define USER_H

#include <QString>
#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    enum Status {
        Offline,
        Online,
        Busy
    };

    User(QObject *parent = nullptr);
    virtual ~User();

    QString id() const;
    void setid(const QString &id);

    QString name() const;
    void setname(const QString &name);

    Status status() const;
    void setstatus(Status status);

    void logout();

protected:
    QString m_id;
    QString m_name;
    Status m_status;
};

#endif // USER_H
