// Reuben Chavez
// 4/29/22
// spring 2022

// Library
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "BOARD.h"

/**
 * This function starts a new linked list. Given an allocated pointer to data it will return a
 * pointer for a malloc()ed ListItem struct. If malloc() fails for any reason, then this function
 * returns NULL otherwise it should return a pointer to this new list item. data can be NULL.
 *
 * @param data The data to be stored in the first ListItem in this new list. Can be any valid 
 *             pointer value.
 * @return A pointer to the malloc()'d ListItem. May be NULL if an error occured.
 */
ListItem *LinkedListNew(char *data)
{
    ListItem *li = (ListItem *) malloc(sizeof (ListItem));
    li->nextItem = NULL;
    li->previousItem = NULL;
    li->data = data;

    return li; // return pointer if malloc works, NULL otherwise
}

/**
 * This function allocates a new ListItem containing data and inserts it into the list directly
 * after item. It rearranges the pointers of other elements in the list to make this happen. If
 * passed a NULL item, CreateAfter() should still create a new ListItem, just with no previousItem.
 * It returns NULL if it can't malloc() a new ListItem, otherwise it returns a pointer to the new
 * item. The data parameter is also allowed to be NULL.
 *
 * @param item The ListItem that will be before the newly-created ListItem.
 * @param data The data the new ListItem will point to.
 * @return A pointer to the newly-malloc()'d ListItem.
 */
ListItem *LinkedListCreateAfter(ListItem *item, char *data)
{
    // Creates new malloc() allocated List Item
    ListItem *ca = LinkedListNew(data);

    // case *item is null
    if (item == NULL) {
        return ca;
    }
    // case A <-> C turns to A <-> B <-> C 
    if (item->nextItem != NULL) {

        // create temp to variable in nexts
        ListItem *next = item->nextItem;
        // set previous item to new item
        next->previousItem = ca;
        // set new item next to next
        ca->nextItem = next;

    }


    // Set *item next item to the newly allocated List Item
    item->nextItem = ca;
    // Set newly made items previous to item
    ca->previousItem = item;
    return ca;
}

/**
 * This function will remove a list item from the linked list and free() the memory that the
 * ListItem struct was using. It doesn't, however, free() the data pointer and instead returns it
 * so that the calling code can manage it.  If passed a pointer to NULL, LinkedListRemove() should
 * return NULL to signal an error.
 *
 * @param item The ListItem to remove from the list.
 * @return The data pointer from the removed item. May be NULL.
 */
char *LinkedListRemove(ListItem *item)
{
    if (item == NULL) {
        return NULL;
    }

    ListItem *prev = item->previousItem; // p <-> i
    ListItem *next = item->nextItem; // i <-> n
    char *data;// store return type
    
    // single Linked List
    if (prev == NULL && next == NULL) {
        data = item->data;
        free(item);
        item = NULL;
        return data;
        //head of linked List w/ Item > 1     
    } else if (prev == NULL && next != NULL) {
        next->previousItem = NULL;
        item->nextItem = NULL;
        data = item->data;
        free(item);
        item = NULL;
        return data;

        // end of Linked List w/ Item > 1
    } else if (prev != NULL && next == NULL) {
        prev->nextItem = NULL;
        item->previousItem = NULL;
        data = item->data;
        free(item);
        item = NULL;
        return data;
        // Middle of Linked List w/ Item > 1
    } else if (prev != NULL && next != NULL) {
        prev->nextItem = next;
        next->previousItem = prev;

        item->nextItem = NULL;
        item->previousItem = NULL;

        data = item->data;
        free(item);
        item = NULL;
        return data;
    }


    return NULL; // case of error
}

/**
 * This function returns the total size of the linked list. This means that even if it is passed a
 * ListItem that is not at the head of the list, it should still return the total number of
 * ListItems in the list. A NULL argument will result in 0 being returned.
 *
 * @param list An item in the list to be sized.
 * @return The number of ListItems in the list (0 if `list` was NULL).
 */
int LinkedListSize(ListItem *list)
{
    // if size is zero return NULL
    if (list == NULL) {
        return 0;
    }

    int size = 0; // Initialize Size
    // create ListItem pointer the will iterate through linked list
    ListItem *current = LinkedListGetFirst(list);
    // while the current item not null
    while (current != NULL) {
        current = current->nextItem; // change current to next item
        size++; // increment size
    }
    return size;
}

/**
 * This function returns the head of a list given some element in the list. If it is passed NULL,
 * it will just return NULL. If given the head of the list it will just return the pointer to the
 * head anyways for consistency.
 *
 * @param list An element in a list.
 * @return A pointer to the first element in the list. Or NULL if provided an invalid list.
 */
ListItem *LinkedListGetFirst(ListItem *list)
{
    // checks that parameter isn't NULL
    if (list == NULL) {
        return NULL;
    }
    // Set current to list parameter
    ListItem *current = list;

    // Traverse to left till meets NULL
    while (current->previousItem != NULL) {
        current = current->previousItem;
    }
    // return head of linked list
    return current;
}

/**
 * This function operates identically to LinkedListGetFirst(), but returns
 * the tail of a linked list.
 * 
 * @param list An element in a list.
 * @return A pointer to the last element in the list. Or NULL if provided an invalid list.
 */
ListItem *LinkedListGetLast(ListItem *list)
{
    // checks that parameter isn't NULL
    if (list == NULL) {
        return NULL;
    }
    // Set current to list parameter
    ListItem *current = list;
    // Traverse till at the end if the list
    while (current->nextItem != NULL) {
        current = current->nextItem;
    }
    // return tail of linked list
    return current;
}

/**
 * LinkedListSwapData() switches the data pointers of the two provided ListItems. This is most
 * useful when trying to reorder ListItems but when you want to preserve their location. This
 * function should return STANDARD_ERROR if either arguments are NULL, otherwise it should return
 * SUCCESS. If one or both of the data pointers are NULL in the given ListItems, it still does
 * perform the swap and returns SUCCESS.
 *
 * @param firstItem One of the items whose data will be swapped.
 * @param secondItem Another item whose data will be swapped.
 * @return SUCCESS if the swap worked or STANDARD_ERROR if it failed.
 */
int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem)
{
    // checks that both arguments are not null
    if (firstItem == NULL || secondItem == NULL) {
        return STANDARD_ERROR;
    }

    char *temp = firstItem->data; // create temp to contain firstItem info
    firstItem->data = secondItem->data; // set firstItem
    secondItem->data = temp;

    return SUCCESS;

}

/**
 * LinkedListPrint() prints out the complete list to stdout. This function prints out the given
 * list, starting at the head if the provided pointer is not the head of the list, like "[STRING1,
 * STRING2, ... ]" If LinkedListPrint() is called with a NULL list it does nothing, returning
 * STANDARD_ERROR. If passed a valid pointer, prints the list and returns SUCCESS.
 *
 * @param list Any element in the list to print.
 * @return SUCCESS or STANDARD_ERROR if passed NULL pointers.
 */
int LinkedListPrint(ListItem *list)
{
    // Check parameter is null
    if (list == NULL) {
        // return STANDARD_ERROR otherwise
        return STANDARD_ERROR;
    }

    // set size to current list size
    int size = LinkedListSize(list);
    ListItem *current = LinkedListGetFirst(list);
    
    //print null<-> indicates head
    printf("\t[NULL<->");
    for (int i = 0; i < size; i++) {
        // if last item
        if (i == size - 1) {
            // don't include <->
            printf("%s", current->data);
        // otherwise if not null
        } else if (current != NULL) {
            // print data pointer of current
            printf("%s<->", current->data);
        }
        // traverse to next point
        current = current->nextItem;

    }
    //print <->null indicates tail
    printf("<->NULL]\n");

    return SUCCESS;
}
