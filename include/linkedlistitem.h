#ifndef LINKEDLISTITEM_H
#define LINKEDLISTITEM_H

/**
 * A linked list element that has a reference to an item as well
 * as the previous and next linked list entries.
 */
class LinkedListItem
{
private:
    /**
     * The previous list item in the list or nullptr if this is
     * the first item.
     */
    LinkedListItem *m_previous;

    /**
     * The next list item in the list or nullptr if this is
     * the last item.
     */
    LinkedListItem *m_next;

    /**
     * The item referenced by this list item.
     */
    void *m_item;

public:
    /**
     * Instantiates a new instance of the EventListItem class.
     *
     * @param item The item to be tracked in the list.
     * @param previous The previous list item that will come before this item.
     * @param next The next list item that will come after this item.
     */
    LinkedListItem(void *item, LinkedListItem *previous, LinkedListItem *next);

    /**
     * Sets the previous list item.
     * 
     * @param previous The previous item.
     */
    void setPrevious(LinkedListItem *previous);

    /**
     * Gets the previous list item.
     */
    LinkedListItem *getPrevious();

    /**
     * Sets the next list item.
     * 
     * @param next The next item.
     */
    void setNext(LinkedListItem *next);

    /**
     * Gets the next list item.
     */
    LinkedListItem *getNext();

    /**
     * Gets the item.
     */
    void *getItem();
};

#endif
