#ifndef COUNTER_USECASE_H
#define COUNTER_USECASE_H

#include "data/counter_data.h"
#include "presentation/counter.h"
#include "usecase/bases/counter_data_interface.h"

class CounterUseCase
{
public:
    CounterUseCase(std::shared_ptr<CounterDataInterface> data);

    void save();
    void append();
    void remove(const QString& id);

    std::vector<Counter> counters() const;

private:
    std::shared_ptr<CounterDataInterface> m_data;
};

#endif // COUNTER_USECASE_H
