#include "eventsource.h"

#ifndef TRIGGEREDEVENTSOURCE_H
#define TRIGGEREDEVENTSOURCE_H

/**
 * An EventSource that is only executed once it is triggered.
 */
class TriggeredEventSource : public EventSource
{
private:
    /**
     * true if the event is triggered and should be executed.
     */
    bool m_triggered = false;

protected:
    /**
     * Sets the state of the event to triggered to indicate that it should
     * be executed.
     */
    void setTriggered();

    /**
     * Clears the triggered state of this event.
     */
    void clearTriggered();

public:
    /**
     * Runs all logic required for the event to be processed.
     */
    virtual void processEvent() override;

    /**
     * Check to see if the event should be triggered.
     */
    virtual void checkEvent();

    /**
     * Executes the user-level event processing code.
     */
    virtual void executeEvent() = 0;

    /**
     * Checks if the event has been triggered.
     * 
     * @returns true if the event has been triggered.
     */
    bool isTriggered();
};

#endif
