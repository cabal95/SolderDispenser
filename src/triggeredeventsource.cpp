#include "triggeredeventsource.h"

/**
 * Sets the state of the event to triggered to indicate that it should
 * be executed.
 */
void TriggeredEventSource::setTriggered()
{
    m_triggered = true;
}

/**
 * Clears the triggered state of this event.
 */
void TriggeredEventSource::clearTriggered()
{
    m_triggered = false;
}

/**
 * Checks if the event has been triggered.
 * 
 * @returns true if the event has been triggered.
 */
bool TriggeredEventSource::isTriggered()
{
    return m_triggered;
}

/**
 * Runs all logic required for the event to be processed.
 */
void TriggeredEventSource::processEvent()
{
    checkEvent();
    
    //
    // If the event has been triggered then we need to execute it and
    // also clear the trigger.
    //
    if (isTriggered())
    {
        clearTriggered();
        executeEvent();
    }
}
