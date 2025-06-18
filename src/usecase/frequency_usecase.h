#ifndef FREQUENCY_USECASE_H
#define FREQUENCY_USECASE_H
#include "usecase/bases/counter_data_interface.h"

#include <chrono>

class FrequencyUseCase
{
public:
    FrequencyUseCase(std::shared_ptr<CounterDataInterface> data);

    double frequency() const;

private:
    std::shared_ptr<CounterDataInterface> m_data;

    mutable double m_lastSum = 0;
    mutable std::chrono::steady_clock::time_point m_lastTimePoint;
};

#endif // FREQUENCY_USECASE_H
