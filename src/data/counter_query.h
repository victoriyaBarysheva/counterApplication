#ifndef COUNTER_QUERY_H
#define COUNTER_QUERY_H

#include "database.h"
#include "usecase/bases/counter_query_interface.h"

class CounterQueryData : public CounterQueryDataInterface
{
public:
    CounterQueryData(std::shared_ptr<DataBaseInterface> db);

    void initialize();

    bool createTable() override;

    // query
    QSet<QString> ids() const override;

    void remove(const QString& id) const override;
    void remove(const QSet<QString>& ids) const override;

    CounterContainer load() const override;
    void save(const CounterContainer& counters) const override;

private:
    std::shared_ptr<DataBaseInterface> m_db;
};

#endif // COUNTER_QUERY_H
