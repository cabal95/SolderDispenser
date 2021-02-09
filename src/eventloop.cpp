#include "eventloop.h"

/**
 * Adds a new event to be tracked.
 * 
 * @param event The event that will be tracked by this RunLoop.
 */
void EventLoop::addEvent(BaseEvent *event)
{
    LinkedListItem *newItem = new LinkedListItem(event, nullptr, m_firstSource);

    m_firstSource = newItem;
}

/**
 * Removes an existing event source from the loop.
 *
 * @param event The event that will no longer be tracked.
 */
void EventLoop::removeEvent(BaseEvent *event)
{
    for (LinkedListItem *item = m_firstSource; item != nullptr; item = item->getNext())
    {
        if (item->getItem() == event)
        {
            removeEvent(item);
            return;
        }
    }
}

/**
 * Remove the item from the internal linked list.
 *
 * @param item The linked list item to be removed.
 */
void EventLoop::removeEvent(LinkedListItem *item)
{
    LinkedListItem *nextItem = item->getNext();

    //
    // Update either the last item or the first item to point
    // to the next item after this one.
    //
    if (item->getPrevious() != nullptr)
    {
        item->getPrevious()->setNext(nextItem);
    }
    else
    {
        m_firstSource = nextItem;
    }
    //
    // Update the next item's previous item to point to the
    // item before this one.
    //
    if (nextItem != nullptr)
    {
        nextItem->setPrevious(item->getPrevious());
    }

    delete item;
}

/**
 * Perform a single pass of the RunLoop and check all events
 * to see if any need to be executed.
 */
void EventLoop::runOnce()
{
    LinkedListItem *item = m_firstSource;

    while (item != nullptr)
    {
        BaseEvent *event = (BaseEvent *)item->getItem();

        //
        // Give the event source a chance to trigger itself.
        //
        event->checkEvent();

        //
        // If the event has been triggered then we need to execute it and
        // also clear the trigger.
        //
        if (event->isTriggered())
        {
            event->clearTriggered();
            event->executeEvent();
        }

        //
        // If the event has completed then it doesn't need to run anymore.
        //
        if (event->isCompleted())
        {
            LinkedListItem *nextItem = item->getNext();

            removeEvent(item);

            item = nextItem;
        }
        else
        {
            item = item->getNext();
        }
    }
}
