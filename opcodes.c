#include <string.h>
#include "monty.h"
extern stack_t *stack;

/**
 * push - pushes an element to the stack
 *
 * @n: integer or element to push.
 * @lineNum: line number of current opcode
 *
 * Return: 1 on success; 0 on failure.
 */
int push(char *n, int lineNum)
{
	int number, stackIsNull = stack == NULL;
	stack_t *newElmnt, *top = getTopElement();

	if (n == NULL || !strcmp(n, ""))
	{
		fprintf(stderr, "L%d: usage: push integer\n", lineNum + 1);
		return (0); /* indicate failure */
	}

	if (isNumber(n)) /* check if input is a valid number */
		number = atoi(n); /* set value for number */
	else /* print error msg */
	{
		fprintf(stderr, "L%d: usage: push integer\n", lineNum + 1);
		return (0); /* indicate failure */
	}

	newElmnt = malloc(sizeof(stack_t)); /* malloc new element */
	if (newElmnt == NULL) /* malloc fail check */
	{
		fprintf(stderr, "Error: malloc failed\n");
		return (0); /* indicate failure */
	}

	/* init newElmnt */
	newElmnt->n = number;
	newElmnt->prev = top; /* top is null if stack is empty (null) */
	newElmnt->next = NULL;
	if (stackIsNull)
		stack = newElmnt; /* make stack point to newElmnt */
	else
		top->next = newElmnt; /* set old top elmnt's next ptr to newElmnt */

	return (1); /* indicate success */
}

/**
 * pop - removes the element at the top of the stack
 *
 * @lineNum: line number this was called on in the Monty script
 * Return: 1 on success, or 0 if the stack is empty to indicate failure.
 */
int pop(int lineNum)
{
	stack_t *top = getTopElement();

	if (stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", lineNum + 1);
		return (0); /* indicate failure */
	}

	/* remove top element and update new top element's next ptr */
	if (top->prev != NULL)
	{
		top->prev->next = NULL;
		top = NULL; /* free(top); caused a segfault */
	}
	else
		stack = NULL;

	return (1);
}

/**
 * pall - prints all values on the stack starting from the top.
 * @lineNum: line number of current opcode
 */
void pall()
{
	stack_t *i = getTopElement();

	while (i != NULL)
	{
		printf("%d\n", i->n);
		i = i->prev;
	}
}

/**
 * pint - prints the number at the top of the stack
 * @lineNum: line number this was called on in the Monty script
 * Return: 1 on success, or 0 if the stack is empty to indicate failure.
 */
int pint(int lineNum)
{
	stack_t *top = getTopElement();

	if (stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", lineNum + 1);
		return (0); /* indicate failure */
	}

	printf("%d\n", top->n);

	return (1);
}

/**
 * getTopElement - gets the element at the top of the stack
 * @stack: pointer to the stack
 * Return: last element in the stack, or null if stack is empty.
 */
stack_t *getTopElement()
{
	stack_t *tail = stack;

	if (stack == NULL)
		return (NULL);

	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	return (tail);
}

/**
 * isNumber - check for non-number characters in the string.
 * If the given string has any non-number characters in it,
 * return 0.
 *
 * @number: character array to be checked if it's all numbers
 *
 * Return: 1 if it's all numbers; 0 if not.
 */
int isNumber(char *number)
{
	unsigned int i;

	for (i = 0; i < strlen(number); i++)
	{
		if (number[i] > '9' || number[i] < '0')
			return (0);
	}

	return (1);
}
