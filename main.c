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
	}

//	opcodes[0] = (instruction_t) {.opcode = "push", .f = push(0, 0, &stack)};

	/* TODO: read file and execute its code */
	instructions = get_file_contents(argv[1]); /* read file and get contents */

	parse_instructions(instructions, parsedInstructions);
	execute_instructions(parsedInstructions, stack); /* execute instructions */
	return (EXIT_SUCCESS);
}

void parse_instructions(char *instructions, char ***dest)
{
	int parsedLine= 0, parsedWord = 0, parsedLetter = 0;
	while (*instructions)
	{
		if (*instructions != '\n' && *instructions != ' ')
		{
			dest[parsedLine][parsedWord][parsedLetter] = *instructions;
			parsedLetter++;
		}
		else if (*instructions == ' ')
		{
			/* TODO: probably need to add a null byte */
			parsedWord++;
			parsedLetter = 0;
		}
		else
		{
			/* TODO: may need to add a null byte */
			parsedLine++;
			parsedLetter = 0;
			parsedWord = 0;
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
 * execute_instructions - execute the instructions provided
 *
 * @instructions: the string of instructions TODO: maybe make this the linked list/array of instructions instead.
 * @stack: the stack
 *
 * Return: 1 on success, -1 on failure
 */
int execute_instructions(char ***instructions, stack_t *stack)
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
	char *instructions = malloc(INT_MAX);

	/*instructions = malloc(sizeof(char) * letters + 1);*/

	if (instructions == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	if (filename == NULL/* || instructions == NULL*/)
		return (0);

	fileDesc = open(filename, O_RDONLY);

	if (fileDesc == -1)
	{
		close(fileDesc);
		return (0);
	}

	charsRead = read(fileDesc, instructions, INT_MAX - 1);

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

void execute_instr(instruction_t instruction, stack_t *stack)
{
	/*if (opcodeIs("push"))
		instruction.f(&stack, 0);
	else if (opcodeIs("pall"))
		instruction.f(&stack, 0);*/

}
