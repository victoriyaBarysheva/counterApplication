#ifndef COUNTER_DATA_INTERFACE_H
#define COUNTER_DATA_INTERFACE_H

#include "usecase/entity/counter_entity.h"

class CounterDataInterface
{
public:
    virtual ~CounterDataInterface() = default;

    virtual void append() = 0;
    virtual void save() = 0;
    virtual void remove(const QString& id) = 0;

    virtual double sum() const = 0;
    virtual CounterContainer counters() const = 0;
};
#endif // COUNTER_DATA_INTERFACE_H
