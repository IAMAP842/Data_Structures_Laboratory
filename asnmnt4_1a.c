// using count
#include <stdio.h>
#include <stdlib.h>

typedef struct circularQueue
{
    int size;
    int t, r;
    int count;
    int *array;
} queue;

queue createIntegerQueue(int queueSize)
{
    queue q;
    q.array = NULL;
    q.t = q.r = 0;
    q.size = queueSize;
    q.count = 0;
    q.array = (int *)malloc(queueSize * sizeof(int));

    if (q.array == NULL)
    {
        printf("Can't create Queue");
    }
    else
    {
        printf("Queue created");
    }
    return q;
}

int isIntegerQueueFull(queue *q)
{
    if (q->count == q->size)
    {
        return 1;
    }
    return 0;
}

int isIntegerQueueEmpty(queue *q)
{
    if (q->count == 0)
    {
        return 1;
    }
    return 0;
}

void freeIntegerQueue(queue *q)
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
        printf("Queue already full");
        return -1;
    }
    else
    {
        q->r = (q->r + 1) % q->size;
        q->array[q->r] = d;
        q->count++;
        printf("Enqueued element is: %d\n", d);
        return 0;
    }
}

int dequeueInteger(queue *q)
{
    int g = -1;
    if (isIntegerQueueEmpty(q))
    {
        printf("Queue is Empty");
        return (-99);
    }
    else
    {
        q->t = (q->t + 1) % q->size;
        g = q->array[q->t];
        (q->count)--;
        return g;
    }
}

int main()
{
    queue iq;
    iq.count = 0;
    iq.size = -66;
    int ch, size, eq, dq = -98, qt = -1;

    printf("\nQueue Implementation using Count is as follows\n");
    printf("1. Create queue\n");
    printf("2. Enque integer value\n");
    printf("3. Dequeue integer value\n");
    printf("4. Check queue is empty or not\n");
    printf("5. Check queue is full or not\n");
    printf("6. Check the queue size\n");
    printf("7. Exit\n");

    do
    {
        printf("\nEnter Choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("input size of queue: ");
            scanf("%d", &size);
            iq = createIntegerQueue(size);
            break;

        case 2:
            if (!isIntegerQueueFull(&iq))
            {
                printf("\nEnter integer value for enqueue: ");
                scanf("%d", &eq);
                enqueueInteger(&iq, eq);
            }
            else
            {
                printf("integer value enqueue not allowed as queue is already full\n");
            }
            break;

        case 3:
            dq = dequeueInteger(&iq);
            if (dq != -99)
            {
                printf("\n Dequeued element is %d", dq);
            }
            else
            {
                printf("\n queue is already empty, so can not dequeue");
            }
            break;

        case 4:
            if (isIntegerQueueEmpty(&iq))
            {
                printf("\n integer queue is empty");
            }
            else
            {
                printf("\n integer queue is not empty");
            }
            break;
        case 5:
            if (isIntegerQueueFull(&iq))
            {
                printf("\n integer queue is full");
            }
            else
            {
                printf("\n integer queue is not full");
            }
            break;
        case 6:
            printf("\n queue size is %d", iq.count);
            break;
        case 7:
            printf("\n Code Ended");
            qt = 0;
            freeIntegerQueue(&iq);
            break;

        default:
            printf("\n invalid input");
            break;
        }

    } while (qt != 0);

    return 0;
}