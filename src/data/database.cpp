#include "database.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DataBase::DataBase(const QString& path) :
    DataBaseInterface()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    // make async
}

DataBase::~DataBase()
{
    DataBase::close();
}

void DataBase::initialize()
{
    auto opened = open();
    qDebug() << QString("DataBase open %1").arg(opened ? "succeeded" : "failed");
    qDebug() << "DataBase initialized";
}

bool DataBase::open()
{
    if (!m_db.open())
    {
        qCritical() << "Database error:" << m_db.lastError().text();
        return false;
    }

    return true;
}

void DataBase::close()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DataBase::transaction()
{
    return m_db.transaction();
}

bool DataBase::commit()
{
    return m_db.commit();
}

bool DataBase::rollback()
{
    return m_db.rollback();
}

bool DataBase::executeBatch(const QString& query, const std::vector<std::vector<QVariant>>& params)
{
    QSqlQuery q(m_db);
    if (!q.prepare(query))
    {
        return false;
    }

    for (const auto& values : params)
    {
        for (size_t i = 0; i < values.size(); ++i)
        {
            q.bindValue(i, values[i]);
        }
        if (!q.exec())
        {
            return false;
        }
    }
    return true;
}

bool DataBase::makeTransaction(std::function<bool()> operation)
{
    if (not m_db.transaction())
    {
        qWarning() << "Transaction start failed";
        return false;
    }

    if (operation())
    {
        if (m_db.commit())
        {
            return true;
        }
        qWarning() << "Commit failed:" << m_db.lastError();
    }

    m_db.rollback();
    return false;
}

bool DataBase::execute(const QString& query, const std::vector<QVariant>& params)
{
    QSqlQuery q(m_db);
    q.prepare(query);

    for (const auto& param : params)
    {
        q.addBindValue(param);
    }

    if (!q.exec())
    {
        qWarning() << "Execute error:" << q.lastError().text();
        return false;
    }
    return true;
}

QSqlQuery DataBase::select(const QString& query, const std::vector<QVariant>& params)
{
    QSqlQuery q(m_db);
    q.prepare(query);

    for (const auto& param : params)
    {
        q.addBindValue(param);
    }

    if (!q.exec())
    {
        qWarning() << "Select error:" << q.lastError().text();
    }
    return q;
}
