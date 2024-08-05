#include "monty.h"
/* stack - the global stack */
stack_t *stack = NULL;
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
	if (executeInstructions(parsedInstructions) == 0)
		exitRtn = EXIT_FAILURE;

	end:
	if (parsedInstructions != NULL)
		freeParsedInstr(parsedInstructions);

	if (instructions != NULL)
		free(instructions);

	freeStack();
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
	int parsedLine = 0, parsedWord = 0, parsedLetter = 0, i = 0;

	if (dest == NULL)
		return (1); /* do nothing, but no error */

	dest[0] = malloc(sizeof(char *) * MAX_WORD_CNT); /* word limit of 3 per line */
	if (dest[0] == NULL)
		return (0); /* indicate malloc failure */
	dest[0][0] = malloc(sizeof(char) * MAX_LETTER_CNT); /* char limit of 16 per word (leaving space for long numbers) */
	if (dest[0][0] == NULL)
		return (0); /* indicate malloc failure */

	/*
	 * I parsed	it this way instead of with strtok because I'm not too familiar
	 * with strtok, and I've done something similar on a personal project in
	 * another language. It basically creates an array of lines, which are
	 * arrays of words, which are strings.
	 */
	while (instructions[i])
	{
		if (instructions[i] != '\n' && instructions[i] != ' ' &&
			instructions[i] != '\t') /* set letters if char is not whitespace */
		{
			dest[parsedLine][parsedWord][parsedLetter] = instructions[i];
			parsedLetter++;
		}
		else if ((instructions[i] == ' ' || instructions[i] == '\t') &&
				(i == 0 || (instructions[i - 1] != ' ' &&
				instructions[i - 1] != '\t' &&
				instructions[i - 1] != '\n'))) /* increment to next word */
		{
			dest[parsedLine][parsedWord][parsedLetter] = '\0';
			parsedWord++;
			parsedLetter = 0;
			dest[parsedLine][parsedWord] = malloc(sizeof(char) * MAX_LETTER_CNT);
			if (dest[parsedLine][parsedWord] == NULL)
				return (0); /* indicate malloc failure */
		}
		else if (instructions[i] == '\n') /* increment to next line */
		{
			dest[parsedLine][parsedWord][parsedLetter] = '\0';
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
		i++;
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
 * @instructions: the string of instructions TODO: maybe make this the linked list/array of instructions instead.
 * Return: 1 on success, 0 on failure
 */
int executeInstructions(char ***instructions)
{
	int lineNum = 0;
	char *opcode;

	while (instructions[lineNum])
	{
		opcode = instructions[lineNum][0];
		if (opcode == NULL)
		{
			lineNum++;
			continue;
		}

		if (opcodeIs("push"))
		{
			if (push(instructions[lineNum][1], lineNum) == 0)
				return (0); /* indicate failure */
		}
		else if (opcodeIs("pop"))
		{
			if (pop(lineNum) == 0)
				return (0); /* indicate failure */
		}
		else if (opcodeIs("swap"))
		{
			if (swap(lineNum) == 0)
				return (0); /* indicate failure */
		}
		else if (opcodeIs("pint"))
		{
			if (pint(lineNum) == 0)
				return (0); /* indicate failure */
		}
		else if (opcodeIs("pall"))
		{
			pall();
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
	ssize_t charsRead, totalCharsRead = 0;
	int bufferSize = 1024;
	char *instructions = malloc(sizeof(char) * bufferSize), tempBuffer[256];

	if (instructions == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		return (NULL);
	}

	if (filename == NULL)
	{
		fprintf(stderr, "Error: unknown error\n");
		return NULL;
	}

	fileDesc = open(filename, O_RDONLY);
	if (fileDesc < 0)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		close(fileDesc);
		return (NULL);
	}

	while ((charsRead = read(fileDesc, tempBuffer, sizeof(tempBuffer) - 1)) > 0)
	{
		if (totalCharsRead + charsRead >= bufferSize)
		{ /* if its not done reading */
			char *newInstructions = malloc(bufferSize *= 2); /* doubles the buffer size */
			if (newInstructions == NULL)
			{
				fprintf(stderr, "Error: malloc failed\n");
				close(fileDesc);
				return (NULL);
			}
			memcpy(newInstructions, instructions, totalCharsRead); /* copies the characters read into the new variable */
			free(instructions); /* not needed anymore; we just copied it to newInstructicns */
			instructions = newInstructions; /* update instructions to point to the new buffer */
		}
		memcpy(&instructions[totalCharsRead], tempBuffer, charsRead); /* appends tempBuffer to the instructions string */
		totalCharsRead += charsRead;
	}

	instructions[totalCharsRead] = '\0';
	close(fileDesc);

	return (instructions);
}

/**
 * freeStack - frees the stack from memory
 * @stack the stack to free
 */
void freeStack()
{
	stack_t *tempStackNode = getTopElement();

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
