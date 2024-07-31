#include <string.h>
#include "monty.h"

/**
 * push - pushes an element to the stack
 *
 * @n: integer or element to push.
 */
void push(char *n)
{
	int number;

	if (isNumber(n)) /* check if input is a valid number */
		number = atoi(n); /* set value for number */
	else
	{
		/*
		 * TODO: if n is not a number;
		 *  print the error message, "L<line_number>: usage: push integer," followed
		 *  by a new line, and exit with the status EXIT_FAILURE
		 *
		 */
	}

}

/**
 * isNumber - check for non-number characters in the string.
 * If any of the supplied numbers have non-number characters in them,
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
