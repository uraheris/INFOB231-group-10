#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct node {
    signed int value;
    struct node* next;
};

struct fifo {
    struct node* head;
    struct node* tail;

    // head points to the next node which should be dequeued
    // tail points to the last node which entered
};

struct fifo* mkfifo () {
    // allocate needed memory space
    struct fifo* list = malloc(sizeof(struct fifo));

    // initialize both of the pointers to NULL
    list->head = NULL;
    list->tail = NULL;

    return list;
}

void enqueue ( struct fifo * lst , signed int elt ) {
    // initialize new node
    struct node* newNode = malloc(sizeof(struct node));

    newNode->next = NULL;
    newNode->value = elt;

    if (lst->tail == NULL) {
        // the item is the only one of the list
        lst->tail = newNode;
        lst->head = newNode;
    }
    else {
        // add node to the end of the list
        lst->tail->next = newNode;

        // move tail pointer to the new last item
        lst->tail = lst->tail->next;
    }
}

signed int dequeue ( struct fifo * lst ) {
    // get the next element to be removed
    signed int elt = lst->head->value;

    // get the next element
    struct node* newHead = lst->head->next;

    // free allocated space for the head
    free(lst->head);

    // new head
    lst->head = newHead;

    return elt;
}

void main() {
    struct fifo* testList = mkfifo();

    enqueue(testList, 12);
    enqueue(testList, 42);

    printf("%d\n", dequeue(testList));

    enqueue(testList, 10);

    printf("%d\n", dequeue(testList));
    printf("%d\n", dequeue(testList));
}