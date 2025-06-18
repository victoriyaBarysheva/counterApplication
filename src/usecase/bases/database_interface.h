#ifndef DATABASE_INTERFACE_H
#define DATABASE_INTERFACE_H

#include "usecase/entity/counter_entity.h"

#include <QSqlQuery>

class DataBaseInterface
{
public:
    virtual ~DataBaseInterface() = default;

    virtual bool open() = 0;
    virtual void close() = 0;

    virtual bool transaction() = 0;
    virtual bool commit() = 0;
    virtual bool rollback() = 0;

    virtual bool makeTransaction(std::function<bool()> operation) = 0;
    virtual bool executeBatch(const QString& query,
                      const std::vector<std::vector<QVariant>>& params) = 0;

    virtual bool execute(const QString& query, const std::vector<QVariant>& params = {}) = 0;
    virtual QSqlQuery select(const QString& query, const std::vector<QVariant>& params = {}) = 0;
};

#endif // DATABASE_INTERFACE_H
