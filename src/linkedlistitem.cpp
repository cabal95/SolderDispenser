#include "linkedlistitem.h"


/**
 * Instantiates a new instance of the EventListItem class.
 *
 * @param item The item to be tracked in the list.
 * @param previous The previous list item that will come before this item.
 * @param next The next list item that will come after this item.
 */
LinkedListItem::LinkedListItem(void *item, LinkedListItem *previous, LinkedListItem *next)
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
void LinkedListItem::setPrevious(LinkedListItem *previous)
{
    m_previous = previous;
}
/**
 * Gets the previous list item.
 */
LinkedListItem *LinkedListItem::getPrevious()
{
    return m_previous;
}
/**
 * Sets the next list item.
 * 
 * @param next The next item.
 */
void LinkedListItem::setNext(LinkedListItem *next)
{
    m_next = next;
}
/**
 * Gets the next list item.
 */
LinkedListItem *LinkedListItem::getNext()
{
    return m_next;
}
/**
 * Gets the item.
 */
void *LinkedListItem::getItem()
{
    return m_item;
}