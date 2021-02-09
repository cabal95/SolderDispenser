#include "baseevent.h"
#include "linkedlistitem.h"

#ifndef RUNLOOP_H
#define RUNLOOP_H

/**
 * Tracks and dispatches events.
 */
class EventLoop
{
private:
    /**
     * The first source in our linked list.
     */
    LinkedListItem *m_firstSource = nullptr;

    /**
     * Remove the item from the internal linked list.
     *
     * @param item The linked list item to be removed.
     */
    void removeEvent(LinkedListItem *item);

public:
    /**
     * Adds a new event to be tracked.
     * 
     * @param event The event that will be tracked by this RunLoop.
     */
    void addEvent(BaseEvent *event);

    /**
     * Removes an existing event source from the loop.
     *
     * @param event The event that will no longer be tracked.
     */
    void removeEvent(BaseEvent *event);

    /**
     * Perform a single pass of the RunLoop and check all events
     * to see if any need to be executed.
     */
    void runOnce();
};

#endif
