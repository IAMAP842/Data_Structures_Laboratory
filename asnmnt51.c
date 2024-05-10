#include <stdio.h>
#include <stdlib.h>

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
    printf("After deleting  %d: ", deleteElem);
    printLL(start);

    return 0;
}