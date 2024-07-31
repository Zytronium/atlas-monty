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
	if (argc != 2) /* no file name given */
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	/* TODO: read file and execute its code */
	return (EXIT_SUCCESS);
}

/*
 * note:
 * argv[0]: program name
 * argc[1]: file to process
 */
