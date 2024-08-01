#include <limits.h>
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
	stack_t *stack = NULL;
	char *instructions;

	(void) argv;
	(void) stack;
	if (argc != 2) /* no file name given */
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	/* TODO: read file and execute its code */
	instructions = get_file_contents(argv[1]); /* read file and get contents */
	/* parse instructions and create a linked list of instructions */
	execute_instructions(instructions, stack); /* execute instructions */
	return (EXIT_SUCCESS);
}
/*
 * note:
 * argv[0]: program name
 * argv[1]: file to process
 */

/**
 * execute_instructions - execute the instructions provided
 *
 * @instructions: the string of instructions TODO: maybe make this the linked list/array of instructions instead.
 * @stack: the stack
 *
 * Return: 1 on success, -1 on failure
 */
int execute_instructions(char *instructions, stack_t *stack)
{

	return (1);
}

/**
 * get_file_contents - Reads a file and returns its contents
 *
 * @filename: the name of the file to read
 *
 * Return: the contents of the file, or NULL on failure.
 */
char *get_file_contents(const char *filename) // TODO
{
	int fileDesc;
	ssize_t charsRead;
	char *instructions;

	/*instructions = malloc(sizeof(char) * letters + 1);*/

	if (filename == NULL/* || instructions == NULL*/)
		return (0);

	fileDesc = open(filename, O_RDONLY);

	if (fileDesc == -1)
	{
		close(fileDesc);
		return (0);
	}

	charsRead = read(fileDesc, instructions, INT_MAX);

	if (charsRead <= 0)
	{
		close(fileDesc);
		return (0);
	}

	instructions[charsRead + 1] = '\0';

	/*printedChars = write(STDOUT_FILENO, instructions, charsRead);*/

	close(fileDesc);

	return (instructions);
}
