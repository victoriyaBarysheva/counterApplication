#include "counter_data.h"

CounterData::CounterData(std::shared_ptr<CounterQueryDataInterface> data) :
    m_data(std::move(data))
{
    m_counters = m_data->load();

    m_thread = std::thread(&CounterData::run, this);
}

CounterData::~CounterData()
{
    m_running.store(false, std::memory_order_release);
    if (m_thread.joinable())
    {
        m_thread.join();
    }
}

void CounterData::append()
{
    std::lock_guard lock(m_mutex);
    auto entity = std::make_shared<CounterEntity>();
    m_counters.push_back(entity);
}

void CounterData::remove(const QString& id)
{
    std::lock_guard lock(m_mutex);

    auto it = std::find_if(m_counters.cbegin(),
                           m_counters.cend(),
                           [&id](auto&& counter) {
                               return counter->id() == id;
                           });

    if (it != m_counters.cend())
    {
        m_counters.erase(it);
    }
}

void CounterData::save()
{
    m_data->save(counters());
}

double CounterData::sum() const
{
    double sum = 0;

    auto _counters = counters();
    std::for_each(_counters.cbegin(),
                  _counters.cend(),
                  [&sum](auto&& counter) mutable {
                      sum += counter->value();
                  });

    return sum;
}

CounterContainer CounterData::counters() const
{
    CounterContainer snapShot;
    {
        std::lock_guard lock(m_mutex);
        snapShot = m_counters;
    }
    return snapShot;
}

void CounterData::run()
{
    while (m_running.load(std::memory_order_acquire))
    {
        auto _counters = counters();
        std::for_each(_counters.cbegin(),
                      _counters.cend(),
                      [](auto&& counter) {
                          counter->increment();
                      });

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
