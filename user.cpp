#include "user.h"

User::User(QObject *parent)
    : QObject(parent), m_status(Offline)
{
}

User::~User()
{
}

QString User::id() const
{
    return m_id;
}

void User::setid(const QString &id)
{
    m_id = id;
}

QString User::name() const
{
    return m_name;
}

void User::setname(const QString &name)
{
    m_name = name;
}

User::Status User::status() const
{
    return m_status;
}

void User::setstatus(Status status)
{
    m_status = status;
}

void User::logout()
{
    m_status = Offline;
}
