#include "frequency_usecase.h"

FrequencyUseCase::FrequencyUseCase(std::shared_ptr<CounterDataInterface> data) :
    m_data(std::move(data))
{
    m_lastTimePoint = std::chrono::steady_clock::now();
    m_lastSum = m_data->sum();
}

double FrequencyUseCase::frequency() const
{
    double frequency = 0.;
    double currentSum = m_data->sum();

    auto now = std::chrono::steady_clock::now();
    double timeDiff = std::chrono::duration<double>(now - m_lastTimePoint).count();

    if (timeDiff > 0)
    {
        frequency = (currentSum - m_lastSum) / timeDiff;
    }

    m_lastSum = currentSum;
    m_lastTimePoint = now;

    return frequency;
}
