#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct node
{
    signed int value;
    struct node *next;
};

struct circular
{
    struct node *head;
    struct node *tail;

    // head points to the next node which should be extractd
    // tail points to the last node which entered
};

struct circular *mkcircular()
{
    // allocate needed memory space
    struct circular *list = malloc(sizeof(struct circular));

    // initialize both of the pointers to NULL
    list->head = NULL;
    list->tail = NULL;

    return list;
}

void insert(struct circular *cycle, signed int elt)
{
    // initialize new node
    struct node *newNode = malloc(sizeof(struct node));

    newNode->next = cycle->head;
    newNode->value = elt;

    if (cycle->tail == NULL)
    {
        // the item is the only one of the list
        cycle->tail = newNode;
        cycle->head = newNode;
    }
    else
    {
        // add node to the end of the list
        cycle->tail->next = newNode;

        // move tail pointer to the new last item
        cycle->tail = cycle->tail->next;
    }
}

signed int extract(struct circular *cycle)
{
    // get the next element to be removed
    signed int elt = cycle->head->value;

    // get the next element
    struct node *newHead = cycle->head->next;

    // free allocated space for the head
    free(cycle->head);

    // new head
    cycle->head = newHead;

    return elt;
}

struct node *rotateToEven(struct circular *cycle)
{
    // go through the list until the head value is even
    // stop if every item was checked (meaning there is no even element at all)
    struct node *initialHead = cycle->head;
    do
    {
        cycle->head = cycle->head->next;
        cycle->tail = cycle->tail->next;
    } while (cycle->head->value % 2 != 0 && cycle->head != initialHead);
}

struct node *rotateToOdd(struct circular *cycle)
{
    // go through the list until the head value is odd
    // stop if every item was checked (meaning there is no odd element at all)
    struct node *initialHead = cycle->head;
    do
    {
        cycle->head = cycle->head->next;
        cycle->tail = cycle->tail->next;
    } while (cycle->head->value % 2 == 0 && cycle->head != initialHead);
}

void main()
{
    struct circular *testList = mkcircular();

    insert(testList, 11);
    insert(testList, 41);
    insert(testList, 241);
    insert(testList, 11);

    rotateToEven(testList);

    printf("%d\n", extract(testList));
    printf("%d\n", extract(testList));
    printf("%d\n", extract(testList));
}