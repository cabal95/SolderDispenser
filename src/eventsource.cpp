#include "eventsource.h"

/**
 * Sets the state of the event to completed to indicate that it should
 * be removed from the runloop.
 */
void EventSource::setCompleted()
{
    m_completed = true;
}

/**
 * Checks if the event has completed and should be removed from the
 * runloop.
 * 
 * @returns true if the event is completed.
 */
bool EventSource::isCompleted()
{
    return m_completed;
}
