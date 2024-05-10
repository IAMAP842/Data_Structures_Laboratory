//without using count

#include <stdio.h>
#include <stdlib.h>

typedef struct circularQueue
{
    int size;
    int t, r;
    int *array;
} queue;

queue createIntegerQueue(int queueSize)
{
    queue q;
    q.array = NULL;
    q.t = q.r = 0;
    q.size = queueSize;
    q.array = (int *)malloc(queueSize * sizeof(int));

    if (q.array == NULL)
    {
        printf("cant create queue");
        return q;
    }
    printf("Queue created");
    return q;
}

int isIntegerQueueFull(queue *q)
{
    if ((q->r + 1) % q->size == q->t)
    {
        return 1;
    }
    return 0;
}

int isIntegerQueueEmpty(queue *q)
{
    if (q->t == q->r)
    {
        return 1;
    }
    return 0;
}

int freeIntegerQueue(queue *q)
{
    if (q->array != NULL)
    {
        free(q->array);
    }
}

int enqueueInteger(queue *q, int d)
{
    if (isIntegerQueueFull(q))
    {
        printf("queue already full");
    }
    else
    {
        q->r = (q->r + 1) % q->size;
        q->array[q->r] = d;
        printf("Enqued element is: %d\n", d);
    }
}

int dequeueInteger(queue *q)
{
    int g = -1;
    if (isIntegerQueueEmpty(q))
    {
        printf("queue empty");
    }
    else
    {
         q->t = (q->t + 1) % q->size;
        g = q->array[q->t];
    }
    return g;
}

int main()
{
    queue iq;
    int ch, eq, deq, size, qt = 1;

    printf("\n Queue Implementation without using Count is as follows \n");
    printf("1. Create Queue\n");
    printf("2. Enque integer value\n");
    printf("3. Dequeue integer value\n");
    printf("4. Check Queue is Empty or not\n");
    printf("5. Check Queue is Full or not\n");
    printf("6. Exit\n");

    do
    {
        printf("\nEnter Your Choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("Enter required size of Queue: ");
            scanf("%d", &size);
            size=size+1;
            iq = createIntegerQueue(size);
            break;

        case 2:
            if (!isIntegerQueueFull(&iq))
            {
                printf("\nEnter integer to enqueue: ");
                scanf("%d", &eq);
                enqueueInteger(&iq, eq);
            }
            else
            {
                printf("Can't Enqueue as queue is full\n");
            }
            break;

        case 3:
            if (!isIntegerQueueEmpty(&iq))
            {
                printf("\nDequeued element %d", dequeueInteger(&iq));
            }
            else
            {
                printf("\nqueue is empty so nothing to dequeue");
            }
            break;

        case 4:
            if (isIntegerQueueEmpty(&iq))
            {
                printf("\nInteger Queue is Empty");
            }
            else
            {
                printf("\nInteger Queue is not Empty");
            }
            break;
        case 5:
            if (isIntegerQueueFull(&iq))
            {
                printf("\nInteger Queue Full");
            }
            else
            {
                printf("\nInteger Queue not full");
            }
            break;

        case 6:
            printf("\nCode ended");
            qt = 0;
            freeIntegerQueue(&iq);
            break;

        default:
            printf("\nYou have entered an Invalid input");
            break;
        }

    } while (qt != 0);

    return 0;
}