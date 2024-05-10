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
    stack stc;
    stc.maxsize = stackSize;
    stc.ptr = (int *)malloc(stackSize * sizeof(int));
    return stc;
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
    int sze;
    printf("Enter the size of the stack which you want to provide\n");
    scanf("%d", &sze);
    stack hp = createIntegerStack(sze);
    hp.top = -1;
    for (int i = 0; i < sze; i++)
    {
        printf("Enter element(s)...................\n");
        int ele;
        scanf("%d", &ele);
        pushIntegerStack(&hp, ele);
    }
    printf("now size of your stack : %d\n", hp.top + 1);
    int pr;
    popIntegerStack(&hp, &pr);
    printf("now size after popping is as follows : %d\n", hp.top + 1);
    printf("Popped element is as follows : %d\n", pr);
    printf("empty stack: %d\n", isIntegerStackEmpty(hp));
    printf("full stack: %d\n", isIntegerStackFull(hp));
    freeIntegerStack(&hp);
    return 0;
}