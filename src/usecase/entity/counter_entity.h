#pragma once

#include <QString>
#include <atomic>

class CounterEntity
{
public:
    CounterEntity(int value = 0);
    CounterEntity(const QString& id, int value = 0);

    void increment() noexcept;

    int value() const noexcept;
    QString id() const noexcept;

private:
    QString m_id;
    std::atomic<int> m_value;
};

using CounterPtr = std::shared_ptr<CounterEntity>;
using CounterContainer = std::vector<CounterPtr>;
