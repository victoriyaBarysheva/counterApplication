#include "counter_usecase.h"

CounterUseCase::CounterUseCase(std::shared_ptr<CounterDataInterface> data) :
    m_data(std::move(data))
{
}

void CounterUseCase::append()
{
    m_data->append();
}

void CounterUseCase::remove(const QString& id)
{
    m_data->remove(id);
}

void CounterUseCase::save()
{
    m_data->save();
}

std::vector<Counter> CounterUseCase::counters() const
{
    // adapter to ui
    std::vector<Counter> result;
    auto counterCountainer = m_data->counters();
    for (const auto& counter : counterCountainer)
    {
        result.emplace_back(counter->id(), counter->value());
    }
    return result;
}
