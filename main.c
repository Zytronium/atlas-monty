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
	int exitRtn = EXIT_SUCCESS;
	char *instructions = NULL, ***parsedInstructions = NULL;

	if (argc != 2) /* no file name given */
	{
		fprintf(stderr, "USAGE: monty file\n");
		exitRtn = EXIT_FAILURE;
		goto end;
		/*argv[1] = "/home/SmartFridge/CLionProjects/atlas-monty/test_code.m";*/
	}

	parsedInstructions = malloc(sizeof(char **) * MAX_LINE_CNT); /*char limit of 1023 + null byte */
	if (parsedInstructions == NULL)
	{
		fprintf(stderr, "Error: malloc failed");
		exitRtn = EXIT_FAILURE;
		goto end;
	}

	instructions = getFileContents(argv[1]); /* read file and get contents */

	if (instructions == NULL)
	{
		exitRtn = EXIT_FAILURE;
		goto end;
	}
	if (parseInstructions(instructions, parsedInstructions) == 0)
	{
		fprintf(stderr, "Error: malloc failed");
		exitRtn = EXIT_FAILURE;
		goto end;
	}
	if (executeInstructions(parsedInstructions, stack) == 0)
		exitRtn = EXIT_FAILURE;

	if (!exitRtn)
	{
		fprintf(stderr, "L%d: usage: push integer\n", 4);
		fprintf(stdout, "file contents: %s\n", instructions);
		exitRtn = EXIT_FAILURE;
	}

	end:
	if (parsedInstructions != NULL)
		freeParsedInstr(parsedInstructions);

	if (instructions != NULL)
		free(instructions);

	freeStack(stack);
	return (exitRtn);
}

void freeParsedInstr(char ***parsedInstructions)
{
	int i = 0, j = 0;

	if (parsedInstructions == NULL)
		return;

	while (parsedInstructions[i] != NULL)
	{
		while (parsedInstructions[i][j] != NULL)
		{
			if (parsedInstructions[i][j] != NULL)
				free(parsedInstructions[i][j]);
			j++;
		}
		if (parsedInstructions[i] != NULL)
			free(parsedInstructions[i]);
		i++;
		j = 0;
	}
	free(parsedInstructions);
}

int parseInstructions(char *instructions, char ***dest)
{
	int parsedLine = 0, parsedWord = 0, parsedLetter = 0;

	dest[0] = malloc(sizeof(char *) * MAX_WORD_CNT); /* word limit of 3 per line */
	if (dest[0] == NULL)
		return (0); /* indicate malloc failure */
	dest[0][0] = malloc(sizeof(char) * MAX_LETTER_CNT); /* char limit of 16 per word (leaving space for long numbers) */
	if (dest[0][0] == NULL)
		return (0); /* indicate malloc failure */

	/*
	 * I parsed				 it this way instead of with strtok because I'm not too familiar
	 * with strtok, and I've done something similar on a personal project in
	 * another language. It basically creates an array of lines, which are
	 * arrays of words, which are strings.
	 */
	while (*instructions)
	{
		if (*instructions != '\n' && *instructions != ' ' &&
			*instructions != '\t')
		{
			dest[parsedLine][parsedWord][parsedLetter] = *instructions;
			parsedLetter++;
		}
		else if (*instructions == ' ' || *instructions == '\t')
		{
			/* TODO: probably need to add a null byte */
			parsedWord++;
			parsedLetter = 0;
			dest[parsedLine][parsedWord] = malloc(sizeof(char) * MAX_LETTER_CNT);
			if (dest[parsedLine][parsedWord] == NULL)
				return (0); /* indicate malloc failure */
		}
		else
		{
			/* TODO: may need to add a null byte */
			parsedLine++;
			parsedLetter = 0;
			parsedWord = 0;
			dest[parsedLine] = malloc(sizeof(char *) * MAX_WORD_CNT);
			if (dest[parsedLine] == NULL)
				return (0); /* indicate malloc failure */
			dest[parsedLine][parsedWord] = malloc(sizeof(char) * MAX_LETTER_CNT);
			if (dest[parsedLine][parsedWord] == NULL)
				return (0); /* indicate malloc failure */
		}
		instructions++;
	}
	return (1);
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
 * Return: 1 on success, 0 on failure
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
			if (push(instructions[lineNum][1], lineNum, &stack) == 0)
				return (0); /* indicate failure */
		}
		else if (opcodeIs("pall"))
		{
			pall(lineNum, stack);
		}
		else if (!opcodeIs("nop") && !opcodeIs(""))
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", lineNum + 1, opcode);
			return (0); /* indicate failure */
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
	char *instructions = malloc(MAX_FILE_SIZE);

	if (instructions == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		return (NULL);
	}

	if (filename == NULL)
	{
		fprintf(stderr, "Error: unknown error\n");
		return (NULL);
	}

	fileDesc = open(filename, O_RDONLY);
	if (fileDesc < 0)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		close(fileDesc);
		return (NULL);
	}

	charsRead = read(fileDesc, instructions,  MAX_FILE_SIZE - 1); /* file size limit */

	instructions[charsRead + 1] = '\0';
	close(fileDesc);

	return (instructions);
}

/**
 * freeStack - frees the stack from memory
 * @stack the stack to free
 */
void freeStack(stack_t *stack)
{
	stack_t *tempStackNode = getTopElement(stack);

	if (stack == NULL)
		return;

	if (tempStackNode != NULL)
	{
		while (tempStackNode->prev != NULL)
		{
			tempStackNode = tempStackNode->prev;
			free(tempStackNode->next);
		}
		free(tempStackNode);
	}
}
