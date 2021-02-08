#include "baseevent.h"

/**
 * Sets the state of the event to triggered to indicate that it should
 * be executed.
 */
void BaseEvent::setTriggered()
{
    m_triggered = true;
}

/**
 * Clears the triggered state of this event.
 */
void BaseEvent::clearTriggered()
{
    m_triggered = false;
}

/**
 * Checks if the event has been triggered.
 * 
 * @returns true if the event has been triggered.
 */
bool BaseEvent::isTriggered()
{
    return m_triggered;
}

/**
 * Sets the state of the event to completed to indicate that it should
 * be removed from the runloop.
 */
void BaseEvent::setCompleted()
{
    m_completed = true;
}

/**
 * Checks if the event has completed and should be removed from the
 * runloop.
 * 
 * @returns true if the event is completed.
 */
bool BaseEvent::isCompleted()
{
    return m_completed;
}

/**
 * Runs logic to determine if the event should be triggered. Overrides
 * should internally call setTriggered() if to trigger the event.
 */
void BaseEvent::checkEvent()
{
}
