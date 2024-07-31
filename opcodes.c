#include <string.h>
#include "monty.h"

/**
 * push - pushes an element to the stack
 *
 * @n: integer or element to push.
 * @lineNum: line number of current opcode
 */
void push(char *n, int lineNum, stack_t *stack)
{
	int number;
	stack_t *newElmnt;

	if (isNumber(n)) /* check if input is a valid number */
		number = atoi(n); /* set value for number */
	else /* print error msg */
		fprintf(stderr, "L%d: usage: push integer\n", lineNum);

	newElmnt = malloc(sizeof(stack_t)); /* malloc new element */
	if (newElmnt == NULL) /* malloc fail check */
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	/* init newElmnt */
	newElmnt->n = number;
	newElmnt->prev = getTopElement(stack);
	newElmnt->next = NULL;
	getTopElement(stack)->next = newElmnt;
}

/**
 * pass - prints all values on the stack starting from the top.
 *
 * @lineNum: line number of current opcode
 */
void pall(int lineNum, stack_t *stack)
{
	stack_t *i = getTopElement(stack);

	(void) lineNum;

	while (i != NULL)
	{
		printf("%d\n", i->n);
		i = i->prev;
	}
}

/**
 * getTopElement - gets the element at the top of the stack
 * Return: last element in the stack
 */
stack_t *getTopElement(stack_t *stack)
{
	stack_t *tail = stack;

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
