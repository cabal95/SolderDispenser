#ifndef EVENTSOURCE_H
#define EVENTSOURCE_H

/**
 * Abstract implementation that all run loop event sources must
 * inherit from.
 */
class EventSource
{
private:
    /**
     * true if the event is complete and should be removed from the runloop.
     */
    bool m_completed = false;

protected:
    /**
     * Sets the state of the event to completed to indicate that it should
     * be removed from the runloop.
     */
    void setCompleted();

public:
    /**
     * Runs all logic required for the event to be processed.
     */
    virtual void processEvent() = 0;

    /**
     * Checks if the event has completed and should be removed from the
     * runloop.
     * 
     * @returns true if the event is completed.
     */
    bool isCompleted();
};

#endif
