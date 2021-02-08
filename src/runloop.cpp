#include "runloop.h"

/**
 * Adds a new event to be tracked.
 * 
 * @param event The event that will be tracked by this RunLoop.
 */
void RunLoop::addEvent(BaseEvent *event)
{
    LinkedListItem<BaseEvent> *newItem = new LinkedListItem<BaseEvent>(event, nullptr, m_firstEvent);

    m_firstEvent = newItem;
}

/**
 * Perform a single pass of the RunLoop and check all events
 * to see if any need to be executed.
 */
void RunLoop::runOnce()
{
    LinkedListItem<BaseEvent> *lastItem = nullptr;
    LinkedListItem<BaseEvent> *item = m_firstEvent;

    while (item != nullptr)
    {
        bool removeEvent = false;
        BaseEvent *event = item->getItem();

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

            //
            // If this event was a run-once type even then remove it
            // since it has now run.
            //
            // if (item->isRunOnce())
            // {
            //     removeEvent = item->isRunOnce();
            // }
        }

        //
        // If the event has completed then it doesn't need to run anymore.
        //
        if (event->isCompleted())
        {
            removeEvent = true;
        }

        //
        // If we need to remove the event from our linked list then do so.
        //
        if (removeEvent)
        {
            LinkedListItem<BaseEvent> *nextItem = item->getNext();

            //
            // Update either the last item or the first item to point
            // to the next item after this one.
            //
            if (lastItem != nullptr)
            {
                lastItem->setNext(nextItem);
            }
            else
            {
                m_firstEvent = nextItem;
            }

            //
            // Update the next item's previous item to point to the
            // item before this one.
            //
            if (nextItem != nullptr)
            {
                nextItem->setPrevious(lastItem);
            }

            item = nextItem;
        }
        else
        {
            item = item->getNext();
        }
    }
}
