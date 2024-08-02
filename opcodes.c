#include <string.h>
#include "monty.h"

/**
 * push - pushes an element to the stack
 *
 * @n: integer or element to push.
 * @lineNum: line number of current opcode
 *
 * Return: 1 on success; 0 on failure.
 */
int push(char *n, int lineNum, stack_t **stack)
{
	int number, stackIsNull = *stack == NULL;
	stack_t *newElmnt;

	if (isNumber(n)) /* check if input is a valid number */
		number = atoi(n); /* set value for number */
	else /* print error msg */
	{
		fprintf(stderr, "L%d: usage: push integer\n", lineNum);
		return (0); /* indicate failure */
	}

	newElmnt = malloc(sizeof(stack_t)); /* malloc new element */
	if (newElmnt == NULL) /* malloc fail check */
	{
		fprintf(stderr, "Error: malloc failed\n");
		return (0); /* indicate failure */
	}

	if (stackIsNull) /* malloc stack if it's empty */
	{
		*stack = malloc(sizeof(stack_t));
		if (*stack == NULL) /* malloc fail check */
		{
			fprintf(stderr, "Error: malloc failed\n");
			return (0); /* indicate failure */
		}
		free(newElmnt);
		/* init newElmnt */
		(*stack)->n = number;
		(*stack)->prev = NULL;
		(*stack)->next = NULL;
	}
	else
	{
		/* init newElmnt */
		newElmnt->n = number;
		newElmnt->prev = getTopElement(*stack);
		newElmnt->next = NULL;
		getTopElement(*stack)->next = newElmnt;
	}

	return (1); /* indicate success */
}

/**
 * pass - prints all values on the stack starting from the top.
 * @lineNum: line number of current opcode
 * @stack: pointer to the stack
 */
void pall(int lineNum, stack_t *stack)
{
	stack_t *i = getTopElement(stack);

	(void) lineNum; /* might need later */

	while (i != NULL)
	{
		printf("%d\n", i->n);
		i = i->prev;
	}
}

/**
 * getTopElement - gets the element at the top of the stack
 * @stack: pointer to the stack
 * Return: last element in the stack, or null if stack is empty.
 */
stack_t *getTopElement(stack_t *stack)
{
	stack_t *tail = stack;

	if (tail == NULL)
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
