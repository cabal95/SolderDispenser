#ifndef BASEEVENT_H
#define BASEEVENT_H

/**
 * Abstract implementation that all run loop event sources must
 * inherit from.
 */
class BaseEvent
{
private:
    /**
     * true if the event is triggered and should be executed.
     */
    bool m_triggered = false;

    /**
     * true if the event is complete and should be removed from the runloop.
     */
    bool m_completed = false;

protected:
    /**
     * Sets the state of the event to triggered to indicate that it should
     * be executed.
     */
    void setTriggered();

    /**
     * Sets the state of the event to completed to indicate that it should
     * be removed from the runloop.
     */
    void setCompleted();

public:
    /**
     * Clears the triggered state of this event.
     */
    void clearTriggered();

    /**
     * Runs logic to determine if the event should be triggered. Overrides
     * should internally call setTriggered() if to trigger the event.
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

    /**
     * Checks if the event has completed and should be removed from the
     * runloop.
     * 
     * @returns true if the event is completed.
     */
    bool isCompleted();
};

#endif
