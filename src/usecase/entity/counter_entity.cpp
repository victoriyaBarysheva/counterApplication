#include "counter_entity.h"

#include <QUuid>

CounterEntity::CounterEntity(int value)
{
    m_id = QUuid::createUuid().toString();
    m_value = value;
}

CounterEntity::CounterEntity(const QString& id, int value)
{
    m_id = id;
    m_value = value;
}

void CounterEntity::increment() noexcept
{
    m_value.fetch_add(1, std::memory_order_release);
}

int CounterEntity::value() const noexcept
{
    return m_value.load(std::memory_order_acquire);
}

QString CounterEntity::id() const noexcept
{
    return m_id;
}
