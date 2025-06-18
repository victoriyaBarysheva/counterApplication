#ifndef COUNTER_H
#define COUNTER_H

#include <QString>

struct Counter
{
    Counter(QString id, int val) :
        m_value(val), m_id(id) {}

    int m_value;
    QString m_id;
};
#endif // COUNTER_H
