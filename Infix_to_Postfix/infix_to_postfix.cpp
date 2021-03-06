#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Stack
{
	int top;
	unsigned capacity;
	int* array;
};

struct Stack* createStack(unsigned capacity)
{
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	if (!stack)
		return NULL;

	stack->capacity = capacity;
	stack->top = -1;

	stack->array = (int*)malloc(stack->capacity * sizeof(int));

	if (!stack->array)
		return NULL;
	return stack;
}

int IsEmpty(struct Stack* stack)
{
	return stack->top == -1;
}

void push(struct Stack* stack, char op)
{
	stack->array[++stack->top] = op;

}

char pop(struct Stack* stack)
{
	if (!IsEmpty(stack))
		return stack->array[stack->top--];
	return '#';
}

char peek(struct Stack* stack)
{
	
		return stack->array[stack->top];
}

int IsOperand(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int Prec(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	}
	return -1;
}

int infixToPostfix(char* exp)
{
	int i, k;
	struct Stack* stack = createStack(strlen(exp));
	if (!stack)
		return -1;
	for (i = 0, k = -1; exp[i]; ++i)
	{
		if (IsOperand(exp[i]))
			exp[++k] = exp[i];
		else if (exp[i] == '(')
			push(stack, exp[i]);
		else if (exp[i] == ')')
		{
			while (!IsEmpty(stack) && peek(stack) != '(')
				exp[++k] = pop(stack);
			if (!IsEmpty(stack) && peek(stack) != '(')
				return -1;	//invalid expression
			else
				pop(stack);
		}
		else
		{
			while (!IsEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack)))
				exp[++k] = pop(stack);
			push(stack, exp[i]);
		}

	}
	while (!IsEmpty(stack))
		exp[++k] = pop(stack);
	exp[++k] = '\0';
	printf("%s\n", exp);
}

int main()
{
	char exp[] = "a+b*c+(d*e+f)*g";
	infixToPostfix(exp);
	getchar();
	return 0;
}