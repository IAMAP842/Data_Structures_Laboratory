#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct circularQueue
{
    int size;
    int f, r;
    int count;
    int *arr;
} queue;

queue createIntegerQueue(int queueSize)
{
    queue q;
    q.arr = NULL;
    q.f = q.r = 0;
    q.size = queueSize;
    q.count = 0;
    q.arr = (int *)malloc(queueSize * sizeof(int));

    if (q.arr == NULL)
    {
        printf("could not create queue");
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
    if (q->arr != NULL)
    {
        free(q->arr);
    }
}

int enqueueInteger(queue *q, int d)
{
    if (isIntegerQueueFull(q))
    {
        printf("queue overflows");
        return -1;
    }
    else
    {
        q->r = (q->r + 1) % q->size;
        q->arr[q->r] = d;
        q->count++;
        printf("Enqueued element is: %d\n", d);
        return 0;
    }
}

int dequeueInteger(queue *q)
{
    int dp = -1;
    if (isIntegerQueueEmpty(q))
    {
        printf("Queue Underflows");
        return (-99);
    }
    else
    {
        q->f = (q->f + 1) % q->size;
        dp = q->arr[q->f];
        (q->count)--;
        return dp;
    }
}

int magicRandomise(struct circularQueue *q)
{
    int qElement, rValue;
    for (; q->count > 0;)
    {
        qElement = dequeueInteger(q);
        if (qElement >= 0)
        {
            srand(time(NULL));
            rValue = rand() % 9 + 1;
            printf("Dequeued Element is: %d\n",qElement);
            printf("Rand Value is: %d\n",rValue);
            qElement = qElement - rValue;
            enqueueInteger(q, qElement);
            printf("\n");
        }
        else
        {
            continue;
        }
    }
    if (q->count = 0)
    {
        printf("Queue Underflows");
    }
}

int main()
{
    queue myQueue;
    myQueue.count = 0;
    myQueue.size = -66;
    int choice, Qsize, enQElem, deQElem = -98, quit = -1;

    printf("\n Queue Implementation using Count is as follows\n");
    printf("1. Create Integer Queue\n");
    printf("2. Enque integer value\n");
    printf("3. Dequeue integer value\n");
    printf("4. Check Queue is Empty or not\n");
    printf("5. Check Queue is Full or not\n");
    printf("6. check Queue Size\n");
    printf("7. Run Function \n");
    printf("8. code ended\n");

    do
    {
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: 
            printf("Enter size of Queue: ");
            scanf("%d", &Qsize);
            myQueue = createIntegerQueue(Qsize);
            break;

        case 2: 
            if (!isIntegerQueueFull(&myQueue))
            {
                printf("\nEnter integer to enqueue: ");
                scanf("%d", &enQElem);
                enqueueInteger(&myQueue, enQElem);
            }
            else
            {
                printf("Can't Enqueue as queue is full\n");
            }
            break;

        case 3: 
            deQElem = dequeueInteger(&myQueue);
            if (deQElem != -99)
            {
                printf("\nDequeued element %d", deQElem);
            }
            else
            {
                printf("\nNothing to Dequeue as queue is empty");
            }
            break;

        case 4: 
            if (isIntegerQueueEmpty(&myQueue))
            {
                printf("\nInteger Queue is Empty");
            }
            else
            {
                printf("\nInteger Queue is not Empty");
            }
            break;
        case 5: 
            if (isIntegerQueueFull(&myQueue))
            {
                printf("\nInteger Queue is Full");
            }
            else
            {
                printf("\nInteger Queue is not Full");
            }
            break;

        case 6: 
            printf("\nQueue Element Count is %d", myQueue.count);
            break;
        case 7: 
            magicRandomise(&myQueue);
            printf("\nQueue Randomised by subtracting random value(1-9) from queue elements");
            break;
        case 8: 
            printf("\ncode ended\n");
            quit = 0;
            freeIntegerQueue(&myQueue);
            break;
        default:
            printf("\n Invalid input");
            break;
        }

    } while (quit != 0);

    return 0;
}
