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
	char *instructions, ***parsedInstructions;

	if (argc != 2) /* no file name given */
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
		/*argv[1] = "/home/SmartFridge/CLionProjects/atlas-monty/test_code.m";*/
	}

	parsedInstructions = malloc(INT_MAX);
	if (parsedInstructions == NULL)
	{
		fprintf(stderr, "Error: malloc failed");
		exit(EXIT_FAILURE);
	}

	/* TODO: read file and execute its code */
	instructions = getFileContents(argv[1]); /* read file and get contents */

	parseInstructions(instructions, parsedInstructions);
	executeInstructions(parsedInstructions, stack); /* execute instructions */

	freeParsedInstr(parsedInstructions);
	free(instructions);
	return (EXIT_SUCCESS);
}

void freeParsedInstr(char ***parsedInstructions)
{
	int i = 0, j = 0;

	while (parsedInstructions[i] != NULL)
	{
		while (parsedInstructions[i][j] != NULL)
		{
			free(parsedInstructions[i][j]);
		}
		free(parsedInstructions[i]);
		i++;
	}
	free(parsedInstructions);
}

void parseInstructions(char *instructions, char ***dest)
{
	int parsedLine= 0, parsedWord = 0, parsedLetter = 0;

	dest[0] = malloc(sizeof(char) * 64); /*character limit of 63 + null byte*/
	dest[0][0] = malloc(sizeof(char) * 16); /* char limit of 16 per word (leaving space for long words in comments) */
	while (*instructions)
	{
		if (*instructions != '\n' && *instructions != ' ')
		{
			dest[parsedLine][parsedWord][parsedLetter] = *instructions; /* segfaults here for unknown reason */
			parsedLetter++;
		}
		else if (*instructions == ' ')
		{
			/* TODO: probably need to add a null byte */
			parsedWord++;
			parsedLetter = 0;
			dest[parsedLine][parsedWord] = malloc(sizeof(char) * 16);
		}
		else
		{
			/* TODO: may need to add a null byte */
			parsedLine++;
			parsedLetter = 0;
			parsedWord = 0;
			dest[parsedLine] = malloc(sizeof(char) * 64);
		}
		instructions++;
	}
}
/*
 * note:
 * argv[0]: program name
 * argv[1]: file to process
 */

/**
 * executeInstructions - execute the instructions provided
 *
 * @instructions: the string of instructions TODO: maybe make this the linked list/array of instructions instead.
 * @stack: the stack
 *
 * Return: 1 on success, -1 on failure
 */
int executeInstructions(char ***instructions, stack_t *stack)
{
	int lineNum = 0;
	char *opcode;

	while (instructions[lineNum])
	{
		opcode = instructions[lineNum][0];

		if (opcodeIs("push"))
		{
			push(instructions[lineNum][1], lineNum, stack);
		}
		else if (opcodeIs("pall"))
			pall(lineNum, stack);
		else if (!opcodeIs("nop"))
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", lineNum, opcode);
			exit(EXIT_FAILURE);
		}
		lineNum++;
	}
	return (1);
}

/**
 * getFileContents - Reads a file and returns its contents
 *
 * @filename: the name of the file to read
 *
 * Return: the contents of the file, or NULL on failure.
 */
char *getFileContents(const char *filename)
{
	int fileDesc;
	ssize_t charsRead;
	char *instructions = malloc(INT_MAX);

	/*instructions = malloc(sizeof(char) * letters + 1);*/

	if (instructions == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	if (filename == NULL)
		return (NULL);

	fileDesc = open(filename, O_RDONLY);

	if (fileDesc == -1)
	{
		close(fileDesc);
		return (NULL);
	}

	charsRead = read(fileDesc, instructions, INT_MAX - 1);

	if (charsRead <= 0)
	{
		close(fileDesc);
		return (NULL);
	}

	instructions[charsRead + 1] = '\0';

	close(fileDesc);

	return (instructions);
}
