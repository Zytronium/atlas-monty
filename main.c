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
	int execRtn;
	char *instructions, ***parsedInstructions;

	if (argc != 2) /* no file name given */
	{
		/*fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);*/
		argv[1] = "/home/SmartFridge/CLionProjects/atlas-monty/test_code.m";
	}

	parsedInstructions = malloc(sizeof(char **) * MAX_LINE_CNT); /*char limit of 1023 + null byte */
	if (parsedInstructions == NULL)
	{
		fprintf(stderr, "Error: malloc failed");
		exit(EXIT_FAILURE);
	}

	instructions = getFileContents(argv[1]); /* read file and get contents */

	if (parseInstructions(instructions, parsedInstructions) == 0)
	{
		freeParsedInstr(parsedInstructions);
		free(instructions);
		fprintf(stderr, "Error: malloc failed");
		exit(EXIT_FAILURE);
	}
	/* execute instructions and free memory */
	execRtn = executeInstructions(parsedInstructions, stack);
	freeParsedInstr(parsedInstructions);
	free(instructions);

	return (!execRtn); /*EXIT_SUCCESS if executeInstructions() didn't fail*/
}

void freeParsedInstr(char ***parsedInstructions)
{
	int i = 0, j = 0;

	while (parsedInstructions[i] != NULL)
	{
		while (parsedInstructions[i][j] != NULL)
		{
			free(parsedInstructions[i][j]);
			j++;
		}
		free(parsedInstructions[i]);
		i++;
		j = 0;
	}
	free(parsedInstructions);
}

int parseInstructions(char *instructions, char ***dest)
{
	int parsedLine= 0, parsedWord = 0, parsedLetter = 0;

	dest[0] = malloc(sizeof(char *) * 64); /* line limit of 64 */
	if (dest[0] == NULL)
		return (0); /* indicate malloc failure */
	dest[0][0] = malloc(sizeof(char) * 16); /* char limit of 16 per word (leaving space for long words in comments) */
	if (dest[0][0] == NULL)
		return (0); /* indicate malloc failure */

	/*
	 * I parse it this way instead of with strtok because I'm not too familiar
	 * with strtok, and I've done something similar on a personal project in
	 * another language. It basically creates an array of lines, which are
	 * arrays of words, which are strings.
	 */
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
			if(push(instructions[lineNum][1], lineNum, &stack) == 0)
				return (0); /* indicate failure */
		}
		else if (opcodeIs("pall"))
		{
			pall(lineNum, stack);
		}
		else if (!opcodeIs("nop") && !opcodeIs(""))
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", lineNum, opcode);
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
		exit(EXIT_FAILURE);
	}

	if (filename == NULL)
	{
		free(instructions);
		return (NULL);
	}

	fileDesc = open(filename, O_RDONLY);
	if (fileDesc == -1)
	{
		free(instructions);
		close(fileDesc);
		return (NULL);
	}

	charsRead = read(fileDesc, instructions, MAX_FILE_SIZE - 1); /* file size limit */
	if (charsRead <= 0)
	{
		free(instructions);
		close(fileDesc);
		return (NULL);
	}

	instructions[charsRead + 1] = '\0';
	close(fileDesc);

	return (instructions);
}
