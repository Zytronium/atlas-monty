#include "monty.h"

/**
 * main - entry point
 *
 * @argc: number of args given to run program, including program path&name
 * @argv: args given to run the program
 *
 * Return: 0 (success)
 */
int main(int argc, char *argv[])
{
	int i = 0;

	printf("Command used: ");
	while (i < argc)
	{
		printf("%s ", argv[i]);
		++i;
	}
	putchar('\n');
	if (argc >= 2)
		printf("first arg given as number: %d", atoi(argv[1]));
	return (EXIT_SUCCESS);
}
