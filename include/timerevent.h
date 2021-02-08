#include "baseevent.h"
#include <stdint.h>

#ifndef TIMEREVENT_H
#define TIMEREVENT_H

/**
 * An event that executes on a set interval in milliseconds.
 */
class TimerEvent : public BaseEvent
{
private:
    /**
     * The last time that the event was executed.
     */
    uint64_t m_lastTriggerTime = 0;

    /**
     * The delay in milliseconds between executions of the timer.
     */
    uint32_t m_interval;

    /**
     * The callback function to invoke when the timer elapses.
     */
    void (*m_callback)() = nullptr;

public:
    /**
     * Instantiates a new instance of the TimerEvent class.
     * 
     * @param interval The number of milliseconds between timer executions.
     * @param callback The function to call when the timer executes.
     */
    TimerEvent(uint32_t interval, void (*callback)());

    /**
     * Runs logic to determine if the event should be triggered. Overrides
     * should internally call setTriggered() if to trigger the event.
     */
    virtual void checkEvent() override;

    /**
     * Executes the user-level event processing code.
     */
    void executeEvent();
};

#endif
