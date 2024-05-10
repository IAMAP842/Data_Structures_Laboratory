#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack
{
    int t;
    char *p;
    int maximum_size;
} st;

int crstc(st *stc, int size)
{
    stc->maximum_size = size;
    stc->t = -1;
    stc->p = (char *)malloc(stc->maximum_size * sizeof(char));
    if (stc->p == NULL)
    {
        return 0;
    }
    return 1;
}

int push(st *pStc, char el)
{
    if (pStc->t + 1 >= pStc->maximum_size)
    {
        return 0;
    }
    else
    {
        pStc->p[++pStc->t] = el;
        return 1;
    }
}

int pop(st *pStack, char *ele)
{
    if (pStack->t < 0)
    {
        return 0;
    }
    else
    {
        *ele = pStack->p[pStack->t--];
        return 1;
    }
}

int freest(st *pS)
{
    if (pS == NULL)
        return 0;
    else
    {
        free(pS->p);
        pS->p = NULL;
        return 1;
    }
}

int is_Full(st *pst)
{
    if ((pst->t + 1 == pst->maximum_size) || pst == NULL)
        return 1;
    else
        return 0;
}

int is_Empty(st *pc)
{
    if ((pc->t == -1) || pc == NULL)
        return 1;
    else
        return 0;
}

char insideq(st *stack, int ele)
{
    char ch = stack->p[ele];
    return ch;
}

bool val(char *array, st *stack, int size)
{
    crstc(stack, size);
    for (int i = 0; i < size; i++)
    {
        if ((array[i] == '(') || (array[i] == '{') || (array[i] == '['))
        {
            push(stack, (int)array[i]);
        }
        else if ((array[i] == ')') || (array[i] == '}') || (array[i] == ']'))
        {
            if (!is_Empty(stack))
            {
                if ((array[i] == ')' && insideq(stack, stack->t) == '(') ||
                    (array[i] == '}' && insideq(stack, stack->t) == '{') ||
                    (array[i] == ']' && insideq(stack, stack->t) == '['))
                {
                    char tempo;
                    pop(stack, &tempo);
                }
                else
                    return false;
            }
            else
                return false;
        }
    }
    return is_Empty(stack);
}

int main()
{
    st tempo_stc;
    int maximumsize = 1000;
    char *arr = (char *)malloc(maximumsize * sizeof(char));

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter your mathematical expression: ");
    fgets(arr, maximumsize, stdin);

    int size = 0;
    while (arr[size] != '\0')
    {
        if (arr[size] == '\n')
        {
            arr[size] = '\0';
            break;
        }
        size++;
    }

    if (val(arr, &tempo_stc, size))
    {
        printf("The given mathematical expression is correct.\n");
    }
    else
    {
        printf("The given mathematical expression is incorrect.\n");
    }

    free(arr);
    return 0;
}
