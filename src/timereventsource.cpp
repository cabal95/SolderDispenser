#include "timereventsource.h"
#include <Arduino.h>

/**
 * Instantiates a new instance of the TimerEvent class.
 * 
 * @param interval The number of milliseconds between timer executions.
 * @param callback The function to call when the timer executes.
 */
TimerEventSource::TimerEventSource(uint32_t interval, void (*callback)())
{
    m_interval = interval;
    m_callback = callback;
}

/**
 * Runs logic to determine if the event should be triggered. Overrides
 * should internally call setTriggered() if to trigger the event.
 */
void TimerEventSource::checkEvent()
{
    if (millis() - m_lastTriggerTime >= m_interval)
    {
        setTriggered();
        m_lastTriggerTime = millis();
    }
}

/**
 * Executes the user-level event processing code.
 */
void TimerEventSource::executeEvent()
{
    if (m_callback != nullptr)
    {
        m_callback();
    }
}
