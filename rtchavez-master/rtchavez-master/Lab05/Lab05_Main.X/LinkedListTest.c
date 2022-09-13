// Reuben Chavez
// 4/29/22
// spring 2022

// Library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "BOARD.h"

int TestingLinkedLists()
{
    printf("Welcome to Reuben Chavez test harness\n\n");

    ListItem *list1 = LinkedListNew("letters");

    ListItem *list2 = LinkedListNew("numbers");
    // ********************************************************************************************
    // Testing LinkedListNew()
    printf("Testing LinkedListNew():");
    if (list1 == NULL || list2 == NULL) {
        printf(" Failed to make ListItems\n");
    } else if (strcmp(list1->data, "letters") == 0 && strcmp(list2->data, "numbers") == 0) {
        printf(" PASSED - Created ListItems w/ correct data\n");

    } else {
        printf("\tFAIL - Didn't create ListItems w/ correct data\n");

    }

    printf("\n\tExpected data for list 1: letters \n");
    printf("\tResult for List 1: %s \n\n", list1->data);
    printf("\tExpected data for list 2: numbers \n");
    printf("\tResult for List 2: %s \n", list2->data);

    // ********************************************************************************************
    // Testing LinkedListCreateAfter()
    printf("\nTesting LinkedListCreateAfter():\n");

    // Expected NULL <-> alphabet <-> a <-> NULL
    ListItem *alpha1 = LinkedListCreateAfter(list1, "a");

    // Expected NULL <-> alphabet <-> a <-> c <-> NULL
    ListItem *alpha2 = LinkedListCreateAfter(alpha1, "c");

    // Expected NULL <-> numbers <-> 0 <-> NULL
    ListItem *zero = LinkedListCreateAfter(list2, "0");

    ListItem *ca_1 = list1->nextItem;
    ListItem *ca_2 = list1->nextItem->nextItem;
    ListItem *ca_3 = list2->nextItem;


    if (ca_1 == NULL || ca_2 == NULL || ca_3 == NULL) {
        printf("\tFAILED - Didn't create List Items \n");

    } else if (strcmp(ca_1->data, alpha1->data) == 0
            && strcmp(ca_2->data, alpha2->data) == 0
            && strcmp(ca_3->data, zero->data) == 0) {

        printf("\tPASSED - Three conditions to add ListItem to the end of a LinkedList\n");
    } else {
        printf("\tFAILED - Didn't Create ListItems with correct data\n");
    }

    printf("\n\tExpected: %s, %s, %s\n", alpha1->data, alpha2->data, zero->data);
    printf("\tResults: %s, %s, %s\n\n", ca_1->data, ca_2->data, ca_3->data);

    // test to see node List Item Is made properly without a previous item
    ListItem *none1 = LinkedListCreateAfter(NULL, "none"); // NULL <-> none <-> NULL

    ListItem *none_prev = none1->previousItem;
    ListItem *none_next = none1->nextItem;
    // if linked list with one listItem than first == last
    ListItem *first = LinkedListGetFirst(none1);
    ListItem *last = LinkedListGetLast(none1);


    if (none1 == NULL) {
        printf("\tFAILED - Didn't make ListItem with NULL parameter\n");
    } else if (strcmp(first->data, last->data) == 0 && none_next == NULL && none_prev == NULL) {
        printf("\tPASSED - Two conditions to see when NULL is entered as a parameter\n");
    } else {
        printf("\tFAILED - Two conditions when NULL enter as parameter\n");
    }
    printf("\n\tExpected: none_prev == NULL: true\n");
    printf("\n\tfirst ListItem == last List item : true\n");

    printf("\n\tResult:");
    printf("\n\t previous of ListItem w/ NULL : %s\n", none_prev == NULL ? NULL : none_prev->data);
    printf("\n\tFirst Item data: %s\n\tLast Item data: %s\n\n", first->data, last->data);


    // checking when inputing ListItem in between LinkedList
    ListItem *alpha3 = LinkedListCreateAfter(alpha1, "b");
    ListItem *prev_al3 = alpha3->previousItem;
    ListItem *next_al3 = alpha3->nextItem;

    if (alpha3 == NULL) {
        printf("\tFAILED - Didn't create ListItem in Between LinkedList\n");
    } else if (strcmp(prev_al3->data, alpha1->data) == 0
            && strcmp(alpha3->data, "b") == 0
            && strcmp(next_al3->data, alpha2->data) == 0) {
        printf("\tPASSES - Three conditions when ListItem is placed in between Linked List\n");
    } else {
        printf("\tFAILED - Three conditions when ListItem is placed in between Linked List\n ");
    }

    printf("\n\tExpected: \n\t\talpha1 data: "
            "%s\n\t\talpha2 data: %s\n", alpha1->data, alpha2->data);
    printf("\n\tResult: \n\t\tprevious ListItem of ListItem "
            "between LinkedList: %s\n", prev_al3->data);
    printf("\t\tnext ListListItem of ListItem between LinkedList: %s\n", next_al3->data);

    //Modifying List 2 for future tests 
    ListItem *one, *two, *three, *four, *five, *six, *seven, *eight, *nine;

    one = LinkedListCreateAfter(zero, "1");
    two = LinkedListCreateAfter(one, "2");
    three = LinkedListCreateAfter(two, "3");
    four = LinkedListCreateAfter(three, "4");
    five = LinkedListCreateAfter(four, "5");
    six = LinkedListCreateAfter(five, "6");
    seven = LinkedListCreateAfter(six, "7");
    eight = LinkedListCreateAfter(seven, "8");
    nine = LinkedListCreateAfter(eight, "9");
    // ********************************************************************************************

    // Testing LinkedListGetFirst() and LinkedListGetLast()
    printf("Testing LinkedListGetFirst() and LinkedListGetLast()\n");

    // store expected answers
    char *head = LinkedListGetFirst(alpha1)->data;
    char *mid = alpha3->data;
    char *end = LinkedListGetLast(alpha3)->data;
    char *single = none1->data;

    ListItem *ex_head = LinkedListGetFirst(alpha3);
    ListItem *ex_mid = alpha3;
    ListItem *ex_tail = LinkedListGetLast(alpha3);
    ListItem *ex_single = none1;


    ListItem *ex_head2 = LinkedListGetFirst(zero);
    ListItem *ex_tail2 = LinkedListGetLast(list2);

    // Tests if LinkedListGetFirst() passes
    if (strcmp(ex_head->data, "letters") == 0 && strcmp(ex_head2->data, "numbers") == 0) {
        printf("\tPASSES - LinkedListGetFirst() returned first item in linked list\n");
    } else {
        printf("\tFAILS - LinkedListGetFirst() didn't returned first item in linked list\n");
    }

    int head_pass = 0;
    ListItem *head_iter = list2;
    while (head_iter != NULL) {
        if (strcmp(LinkedListGetFirst(head_iter)->data, "numbers") == 0) {
            head_pass++;
        } else {
            printf("FAILS - at %d index\n", head_pass);
            break;
        }
        head_iter = head_iter->nextItem;
    }

    if (head_pass == 11) {
        printf("\tPASSES - LinkedListGetFirst() is consistent throughout LinkedList\n");
    } else {
        printf("\tFAILS - LinkedListGetFirst() is not consistent throughout LinkedList\n");
    }

    // Tests if LinkedListGetLast() passes
    if (strcmp(ex_tail->data, "c") == 0 && strcmp(ex_tail2->data, "9") == 0) {
        printf("\tPASSES - LinkedListGetLast() returned last item in linked list\n");
    } else {
        printf("FAILS\n");
    }

    int tail_pass = 0;
    ListItem *tail_iter = list2;
    while (tail_iter != NULL) {
        if (strcmp(LinkedListGetLast(tail_iter)->data, "9") == 0) {
            tail_pass++;
        } else {
            printf("\tFAILS - at %d index\n", tail_pass);
            break;
        }
        tail_iter = tail_iter->nextItem;
    }

    if (tail_pass == 11) {
        printf("\tPASSES - LinkedListGetLast() is consistent throughout LinkedList\n");
    } else {
        printf("\tFAILS - LinkedListGetLast() is not consistent throughout LinkedList\n");
    }

    // Testing if LinkedListGetFirst() and LinkedListGetLast() return NULL 
    if (LinkedListGetFirst(NULL) == NULL && LinkedListGetLast(NULL) == NULL) {
        printf("\tPASSES - LinkedListGetFirst() and LinkedListGetLast() returned NULL\n");
    } else {
        printf("FAILS - LinkedListGetFirst() or LinkedListGetLast() don't returned NULL\n");
    }
    // ********************************************************************************************
    //Testing LinkedListRemove()
    printf("Testing LinkedListRemove() && Demonstrating with LinkedListPrint()\n");
    int a = LinkedListPrint(alpha3);

    // removing head of linked list
    char *remove_head = LinkedListRemove(ex_head);
    printf("\tremove head: %s\n", remove_head);

    int b = LinkedListPrint(alpha3);

    if (strcmp(remove_head, head) == 0 && alpha1->previousItem == NULL) {
        printf("\tPASSED - Returned Removed Head of Linked List Correctly\n");
    } else {
        printf("\tFAILED - Didn't Remove Head of Linked List Properly\n");
    }

    // removing mid of Linked list
    char *remove_mid = LinkedListRemove(ex_mid);
    printf("\tremove mid: %s\n", remove_mid);

    int c = LinkedListPrint(alpha1);

    if (strcmp(remove_mid, mid) == 0 && strcmp(alpha1->nextItem->data, alpha2->data) == 0
            && strcmp(alpha1->data, alpha2->previousItem->data) == 0) {
        printf("\tPASSED - Returned Removing Middle of Linked List Correctly\n");
    } else {
        printf("\tFAILED - Didn't Remove Middle of Linked List Properly\n");
    }


    //    alpha3 = LinkedListCreateAfter(alpha1,"b");

    // removing end of linked list
    char *remove_end = LinkedListRemove(ex_tail);
    printf("\tremove end: %s\n", remove_end);

    int d = LinkedListPrint(alpha1);

    if (strcmp(remove_end, end) == 0 && alpha1->nextItem == NULL) {
        printf("\tPASSED - Returned Removed End of Linked List Correctly\n");
    } else {
        printf("\tFAILED - Didn't Remove End of Linked List Properly\n");
    }


    // Note** can work top->mid->end when parameter are initialized beforehand
    // placing the function LinkListGetFirst() or LinkListGetLast() in 
    // LinkListRemove() => seg fault

    printf("\tRemoving from a single linked list");
    int e = LinkedListPrint(none1);
    // removing single item
    char *remove_single = LinkedListRemove(none1);

    if (strcmp(remove_single, single) == 0) {
        printf("\tPASSED - Returned Single Linked List data Correctly\n");
    } else {
        printf("\tFAILED - Didn't Remove End of Linked List Properly\n");
    }

    // removing with null
    char *none2 = LinkedListRemove(NULL);

    if (none2 == NULL) {
        printf("\tPASSED - Returning NULL when seta as a Parameter\n");

    } else {
        printf("\tFAILED - Didn't pass all six conditions");
    }
    // ********************************************************************************************
    // Testing LinkedListPRINT()
    printf("Testing LinkedListPrint():\n");

    int f = LinkedListPrint(NULL);

    if (a == SUCCESS && b == SUCCESS && c == SUCCESS
            && d == SUCCESS && e == SUCCESS && f == STANDARD_ERROR) {
        printf("\tPASSES - All LinkedListPrints() returned "
                "SUCCESS and STANDARD_ERROR respectability\n");
    } else {
        printf("\tFAILS - LinkedListPrints() didn't return "
                "SUCCESS and STANDARD_ERROR respectability\n");
    }

    // *********************************************************************************************

    // Testing Link Size()
    printf("Testing LinkedListSize():\n");

    if (LinkedListSize(zero) == 11) {
        printf("\tPASSES - LinkedList if correct size\n");
    } else {
        printf("\tFails - Size is off\n");
    }

    int status = 0;
    ListItem *current = list2;
    while (current != NULL) {
        if (LinkedListSize(current) == 11) {
            status++;
        } else {
            printf("Stopped at index: %d\n", status);
            break;
        }
        current = current->nextItem;

    }
    if (status == 11) {
        printf("\tPASSES - Size is consistent throughout list\n");
    } else {
        printf("\tFAILS - Size is inconsistent\n");
    }
    // ********************************************************************************************
    // Testing LinkedListSwapData()
    printf("Testing LinkedListSwapData()\n");

    LinkedListPrint(list2);

    int test1 = LinkedListSwapData(zero, nine);
    int test2 = LinkedListSwapData(NULL, five);
    int test3 = LinkedListSwapData(two, NULL);

    if (test1 = SUCCESS && test2 == STANDARD_ERROR && test3 == STANDARD_ERROR) {
        printf("\tPASSES - LinkedListSwapData() returned SUCCESS and STANDARD_ERROR"
                " properly\n");
    } else {
        printf("\tFAILS - LinkedListSwapData() failed");
    }
    LinkedListSwapData(one, eight);
    LinkedListSwapData(two, seven);
    LinkedListSwapData(three, six);
    LinkedListSwapData(four, five);

    printf("\n\tIs List Swapped : \n");
    LinkedListPrint(zero);
    return 0;
}
