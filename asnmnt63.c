#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CharStack
{
    int top;
    unsigned capacity;
    char *array;
};

struct CharStack *createCharStack(unsigned capacity)
{
    struct CharStack *stack = (struct CharStack *)malloc(sizeof(struct CharStack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char *)malloc(stack->capacity * sizeof(char));
    return stack;
}

int isEmpty(struct CharStack *stack)
{
    return stack->top == -1;
}

void push(struct CharStack *stack, char item)
{
    stack->array[++stack->top] = item;
}

char pop(struct CharStack *stack)
{
    return stack->array[stack->top--];
}

char peek(struct CharStack *stack)
{
    return stack->array[stack->top];
}

int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int getPrecedence(char ch)
{
    if (ch == '+' || ch == '-')
    {
        return 1;
    }
    else if (ch == '*' || ch == '/')
    {
        return 2;
    }
    return 0;
}

void infixToPostfix(char *infix, char *postfix)
{
    struct CharStack *stack = createCharStack(strlen(infix));
    int i, j = 0;

    for (i = 0; infix[i]; ++i)
    {
        char c = infix[i];

        if (isalnum(c))
        {
            postfix[j++] = c;
        }
        else if (isOperator(c))
        {
            while (!isEmpty(stack) && peek(stack) != '(' && getPrecedence(c) <= getPrecedence(peek(stack)))
            {
                postfix[j++] = pop(stack);
            }
            push(stack, c);
        }
        else if (c == '(')
        {
            push(stack, c);
        }
        else if (c == ')')
        {
            while (!isEmpty(stack) && peek(stack) != '(')
            {
                postfix[j++] = pop(stack);
            }
            pop(stack);
        }
    }

    while (!isEmpty(stack))
    {
        postfix[j++] = pop(stack);
    }

    postfix[j] = '\0';
}

int main()
{
    char infix_expression[100];
    char postfix_expression[100];

    printf("Enter an infix expression (with +, -, *, / operators): ");
    scanf("%s", infix_expression);

    infixToPostfix(infix_expression, postfix_expression);

    printf("Postfix expression: %s\n", postfix_expression);

    return 0;
}//5+3*2-7