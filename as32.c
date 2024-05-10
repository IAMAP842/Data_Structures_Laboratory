#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int maxsize;
    int top;
    int *ptr;
} stack;
stack createIntegerStack(int stackSize)
{
    stack sp;
    sp.maxsize = stackSize;
    sp.ptr = (int *)malloc(stackSize * sizeof(int));
    return sp;
}
int pushIntegerStack(stack *s, int d)
{
    if (s->top == s->maxsize - 1)
    {
        return 0;
    }
    s->top++;
    s->ptr[s->top] = d;
    return 1;
}
int popIntegerStack(stack *s, int *dp)
{
    if (s->top == -1)
    {
        printf("empty stack\n");
        return 0;
    }
    *dp = s->ptr[s->top];
    s->top--;
    return 1;
}
int freeIntegerStack(stack *s)
{
    if (s == NULL)
        return 0;
    free(s->ptr);
    s->top = -1;
    return 1;
}
int isIntegerStackFull(stack s)
{
    if (s.top + 1 == s.maxsize)
        return 1;
    return 0;
}
int isIntegerStackEmpty(stack s)
{
    if (s.top == -1)
        return 1;
    return 0;
}
int main()
{
    stack sta, stb;
    printf("Enter size of stacka and stackb\n");
    int n, m;
    scanf("%d %d", &n, &m);
    sta = createIntegerStack(n);
    sta.top = -1;
    stb = createIntegerStack(m);
    stb.top = -1;
    int e;
    printf("Enter the elements to fill up the two stacks\n");
    while (1)
    {
        if (isIntegerStackFull(sta) != 1)
        {
            scanf("%d", &e);
            pushIntegerStack(&sta, e);
        }
        else
        {
            scanf("%d", &e);
            pushIntegerStack(&stb, e);
            if (isIntegerStackFull(stb))
                break;
        }
    }
    printf("Printing popped elements..................\n");
    while (1)
    {
        if (isIntegerStackEmpty(stb) != 1)
        {

            popIntegerStack(&stb, &e);
            printf("%d\n", e);
        }
        else
        {
            popIntegerStack(&sta, &e);
            printf("%d\n", e);
            if (isIntegerStackEmpty(sta))
                break;
        }
    }
    return 0;
}