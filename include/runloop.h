#include "baseevent.h"
#include "linkedlistitem.h"

#ifndef RUNLOOP_H
#define RUNLOOP_H

/**
 * Tracks and dispatches events.
 */
class RunLoop
{
private:
    /**
     * The first event in our linked list.
     */
    LinkedListItem<BaseEvent> *m_firstEvent = nullptr;

public:
    /**
     * Adds a new event to be tracked.
     * 
     * @param event The event that will be tracked by this RunLoop.
     */
    void addEvent(BaseEvent *event);

    /**
     * Perform a single pass of the RunLoop and check all events
     * to see if any need to be executed.
     */
    void runOnce();
};

#endif
