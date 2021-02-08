#ifndef LINKEDLISTITEM_H
#define LINKEDLISTITEM_H

/**
 * A linked list element that has a reference to an item as well
 * as the previous and next linked list entries.
 */
template <class TItem>
class LinkedListItem
{
private:
    /**
     * The previous list item in the list or nullptr if this is
     * the first item.
     */
    LinkedListItem<TItem> *m_previous;

    /**
     * The next list item in the list or nullptr if this is
     * the last item.
     */
    LinkedListItem<TItem> *m_next;

    /**
     * The item referenced by this list item.
     */
    TItem *m_item;

public:
    /**
     * Instantiates a new instance of the EventListItem class.
     *
     * @param item The item to be tracked in the list.
     * @param previous The previous list item that will come before this item.
     * @param next The next list item that will come after this item.
     */
    LinkedListItem(TItem *item, LinkedListItem<TItem> *previous, LinkedListItem<TItem> *next)
    {
        m_item = item;
        m_previous = previous;
        m_next = next;
    }

    /**
     * Sets the previous list item.
     * 
     * @param previous The previous item.
     */
    void setPrevious(LinkedListItem<TItem> *previous)
    {
        m_previous = previous;
    }

    /**
     * Gets the previous list item.
     */
    LinkedListItem<TItem> *getPrevious()
    {
        return m_previous;
    }

    /**
     * Sets the next list item.
     * 
     * @param next The next item.
     */
    void setNext(LinkedListItem<TItem> *next)
    {
        m_next = next;
    }

    /**
     * Gets the next list item.
     */
    LinkedListItem<TItem> *getNext()
    {
        return m_next;
    }

    /**
     * Gets the item.
     */
    TItem *getItem()
    {
        return m_item;
    }
};

#endif
