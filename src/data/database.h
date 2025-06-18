#pragma once

#include "usecase/bases/database_interface.h"
#include "usecase/entity/counter_entity.h"

#include <QSqlDatabase>

class DataBase : public DataBaseInterface
{
public:
    DataBase(const QString& path);

    ~DataBase();

    void initialize();

    bool open() override;
    void close() override;

    bool transaction() override;
    bool commit() override;
    bool rollback() override;

    bool makeTransaction(std::function<bool()> operation) override;
    bool executeBatch(const QString& query,
                      const std::vector<std::vector<QVariant>>& params) override;

    bool execute(const QString& query, const std::vector<QVariant>& params = {}) override;
    // QSqlQuery ->variant map
    QSqlQuery select(const QString& query, const std::vector<QVariant>& params = {}) override;

private:
    QSqlDatabase m_db;
};
