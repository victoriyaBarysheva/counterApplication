#include "counter_query.h"

CounterQueryData::CounterQueryData(std::shared_ptr<DataBaseInterface> db) :
    CounterQueryDataInterface(),
    m_db(std::move(db))
{
}

void CounterQueryData::initialize()
{
    auto created = createTable();
    qDebug() << QString("CounterQueryData create table %1")
                    .arg(created ? "succeeded" : "failed");
    qDebug() << "CounterQueryData initialized";
}

bool CounterQueryData::createTable()
{
    return m_db->execute(
        "CREATE TABLE IF NOT EXISTS counters ("
        "   id TEXT PRIMARY KEY,"
        "   value INTEGER NOT NULL"
        ")");
}

QSet<QString> CounterQueryData::ids() const
{
    QSet<QString> ids;
    auto idQuery = m_db->select("SELECT id FROM counters");
    while (idQuery.next())
    {
        ids.insert(idQuery.value("id").toString());
    }
    return ids;
}

void CounterQueryData::remove(const QSet<QString>& ids) const
{
    if (ids.isEmpty())
    {
        return;
    }

    std::vector<QVariant> params;
    QString query = "DELETE FROM counters WHERE id IN (";

    QStringList placeholders;

    for (const auto& id : ids)
    {
        placeholders.append("?");
        params.push_back(id);
    }

    query.append(placeholders.join(",") + ")");

    if (not m_db->execute(query, params))
    {
        return;
    }
}

CounterContainer CounterQueryData::load() const
{
    CounterContainer counters;

    auto query = m_db->select("SELECT id, value FROM counters");
    while (query.next())
    {
        auto id = query.value(0).toString();
        auto value = query.value(1).toInt();
        qDebug() << QString("CounterQueryData load counter id=%1 value=%2")
                        .arg(id, QString::number(value));
        counters.push_back(std::make_shared<CounterEntity>(id, value));
    }

    return counters;
}

void CounterQueryData::remove(const QString& id) const
{
    auto removed = m_db->execute(
        "DELETE FROM counters WHERE id = ?",
        { id });

    qDebug() << QString("CounterQueryData remove counter id=%1 %2")
                    .arg(id, removed ? "succeed" : "failed");
}

void CounterQueryData::save(const CounterContainer& counters) const
{
    qDebug() << "CounterQueryData save counters";

    // remove
    QSet<QString> currentIds;
    std::for_each(counters.cbegin(),
                  counters.cend(),
                  [&currentIds](auto&& counter) mutable {
                      currentIds.insert(counter->id());
                  });

    remove(ids() - currentIds);

    std::vector<std::vector<QVariant>> batchParams;
    for (const auto& counter : counters)
    {
        qDebug() << QString("counter id=%1 value=%2")
                        .arg(counter->id(),
                             QString::number(counter->value()));
        batchParams.push_back({ counter->id(),
                                counter->value(),
                                counter->value() });
    }

    auto saved = m_db->makeTransaction([&batchParams, this]() -> bool {
        // update or insert

        return m_db->executeBatch(
            "INSERT INTO counters (id, value) VALUES (?, ?) "
            "ON CONFLICT(id) DO UPDATE SET value = ?",
            batchParams);
    });

    qDebug() << QString("CounterQueryData save counters %1")
                    .arg(saved ? "succeed" : "failed");
}
