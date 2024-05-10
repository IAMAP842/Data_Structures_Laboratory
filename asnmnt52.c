#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct intNode
{
    int element;
    struct intNode *next;
};

struct intNode *addIntNodeSorted(struct intNode *start, int elem)
{
    struct intNode *newNode = (struct intNode *)malloc(sizeof(struct intNode));
    newNode->element = elem;
    newNode->next = NULL;

    if (start == NULL || elem <= start->element)
    {
        newNode->next = start;
        start = newNode;
        return start;
    }

    struct intNode *current = start;
    while (current->next != NULL && current->next->element < elem)
    {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    return start;
}

int isPresentIntNodeSorted(struct intNode *start, int elem)
{
    int position = 1;
    struct intNode *current = start;

    while (current != NULL)
    {
        if (current->element == elem)
        {
            return position;
        }
        current = current->next;
        position++;
    }

    return 0;
}

struct intNode *deleteIntNodeSorted(struct intNode *start, int elem)
{
    if (start == NULL)
    {
        return start;
    }

    if (start->element == elem)
    {
        struct intNode *temp = start;
        start = start->next;
        free(temp);
        return start;
    }

    struct intNode *current = start;
    while (current->next != NULL && current->next->element != elem)
    {
        current = current->next;
    }

    if (current->next != NULL)
    {
        struct intNode *temp = current->next;
        current->next = temp->next;
        free(temp);
    }

    return start;
}

void printLL(struct intNode *start)
{
    printf("Start -> ");
    struct intNode *current = start;
    while (current != NULL)
    {
        printf("%d -> ", current->element);
        current = current->next;
    }
    printf("NULL\n");
}

struct intNode *freeIntNodeSorted(struct intNode *start)
{
    struct intNode *current = start;
    while (current != NULL)
    {
        struct intNode *temp = current;
        current = current->next;
        free(temp);
    }
    return NULL;
}

struct intNode *reverseIntNodeSorted(struct intNode *start)
{
    struct intNode *prev = NULL;
    struct intNode *current = start;
    struct intNode *next;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

void updateIntNode(struct intNode *start)
{
    struct intNode *current = start;
    srand(time(NULL));

    while (current != NULL)
    {
        current->element += rand() % 10;
        current = current->next;
    }
}

struct intNode *sortIntNode(struct intNode *start)
{
    struct intNode *sorted = NULL;

    while (start != NULL)
    {
        struct intNode *current = start;
        start = start->next;

        if (sorted == NULL || current->element <= sorted->element)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            struct intNode *temp = sorted;
            while (temp->next != NULL && current->element > temp->next->element)
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    return sorted;
}

struct intNode *mergeIntNodeSorted(struct intNode *start1, struct intNode *start2)
{
    if (start1 == NULL)
    {
        return start2;
    }
    if (start2 == NULL)
    {
        return start1;
    }

    struct intNode *merged;
    if (start1->element < start2->element)
    {
        merged = start1;
        start1 = start1->next;
    }
    else
    {
        merged = start2;
        start2 = start2->next;
    }

    struct intNode *current = merged;

    while (start1 != NULL && start2 != NULL)
    {
        if (start1->element < start2->element)
        {
            current->next = start1;
            start1 = start1->next;
        }
        else
        {
            current->next = start2;
            start2 = start2->next;
        }
        current = current->next;
    }

    if (start1 != NULL)
    {
        current->next = start1;
    }
    else
    {
        current->next = start2;
    }

    start1 = NULL;
    start2 = NULL;

    return merged;
}

int main()
{
    struct intNode *start = NULL;

    start = addIntNodeSorted(start, 12);
    start = addIntNodeSorted(start, 5);
    start = addIntNodeSorted(start, 11);
    start = addIntNodeSorted(start, 2);

    printf("Linked List: ");
    printLL(start);

    int searchElem = 5;
    int position = isPresentIntNodeSorted(start, searchElem);
    if (position > 0)
    {
        printf("%d was found at the position %d\n", searchElem, position);
    }
    else
    {
        printf("%d was not found in the given linked list\n", searchElem);
    }

    int deleteElem = 11;
    start = deleteIntNodeSorted(start, deleteElem);
    printf("After deleting %d: ", deleteElem);
    printLL(start);

    start = freeIntNodeSorted(start);
    printf("After freeing the linked list: ");
    printLL(start);

    start = addIntNodeSorted(start, 8);
    start = addIntNodeSorted(start, 3);
    printf("After adding new elements: ");
    printLL(start);

    start = reverseIntNodeSorted(start);
    printf("After reversing: ");
    printLL(start);

    updateIntNode(start);
    printf("After updating elements: ");
    printLL(start);

    start = sortIntNode(start);
    printf("After sorting: ");
    printLL(start);

    struct intNode *start2 = NULL;
    start2 = addIntNodeSorted(start2, 7);
    start2 = addIntNodeSorted(start2, 1);
    start2 = addIntNodeSorted(start2, 4);
    printf("Second Linked List: ");
    printLL(start2);

    start = mergeIntNodeSorted(start, start2);
    printf("After merging: ");
    printLL(start);

    return 0;
}