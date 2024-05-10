#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Stack
{
    int top;
    int capacity;
    int *array;
};

struct Stack *createStack(int capacity)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}

void push(struct Stack *stack, int item)
{
    stack->array[++stack->top] = item;
}

int pop(struct Stack *stack)
{
    return stack->array[stack->top--];
}

int evaluatePostfix(char *expression)
{
    struct Stack *stack = createStack(strlen(expression));
    for (int i = 0; expression[i]; ++i)
    {
        if (isdigit(expression[i]))
        {
            push(stack, expression[i] - '0');
        }
        else
        {
            int operand2 = pop(stack);
            int operand1 = pop(stack);
            switch (expression[i])
            {
            case '+':
                push(stack, operand1 + operand2);
                break;
            case '-':
                push(stack, operand1 - operand2);
                break;
            case '*':
                push(stack, operand1 * operand2);
                break;
            case '/':
                push(stack, operand1 / operand2);
                break;
            }
        }
    }
    return pop(stack);
}

int main()
{
    char postfix_expression[100];
    printf("Enter a postfix expression (single-digit operands): ");
    scanf("%s", postfix_expression);
    int result = evaluatePostfix(postfix_expression);
    printf("Result of the postfix expression is %d\n", result);
    return 0;
}//52+