#ifndef COUNTER_QUERY_INTERFACE_H
#define COUNTER_QUERY_INTERFACE_H

#include "usecase/entity/counter_entity.h"

class CounterQueryDataInterface
{
public:
    virtual ~CounterQueryDataInterface() = default;

    virtual bool createTable() = 0;

    // query

    virtual QSet<QString> ids() const = 0;

    virtual void remove(const QString& id) const = 0;
    virtual void remove(const QSet<QString>& ids) const = 0;

    virtual CounterContainer load() const = 0;
    virtual void save(const CounterContainer& counters) const = 0;
};

#endif // COUNTER_QUERY_INTERFACE_H
