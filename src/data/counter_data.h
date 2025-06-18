#ifndef COUNTER_DATA_H
#define COUNTER_DATA_H

#include "counter_query.h"
#include "usecase/bases/counter_data_interface.h"
#include "usecase/entity/counter_entity.h"

#include <atomic>
#include <mutex>
#include <thread>

class CounterData : public CounterDataInterface
{
public:
    CounterData(std::shared_ptr<CounterQueryDataInterface> data);
    ~CounterData();

    void append() override;
    void save() override;
    void remove(const QString& id) override;

    double sum() const override;
    CounterContainer counters() const override;

private:
    void run();

private:
    std::thread m_thread;
    mutable std::mutex m_mutex;
    std::atomic<bool> m_running { true };

    std::vector<CounterPtr> m_counters;
    std::shared_ptr<CounterQueryDataInterface> m_data;
};

#endif // COUNTER_DATA_H
