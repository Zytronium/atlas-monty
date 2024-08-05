#ifndef MONTY_H
#define MONTY_H

/* ↓ LIBRARIES ↓ */
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/* ------------------- */

/* ↓ STRUCTS AND MISC ↓ */
/**
 * opcodeIs - macro for checking if instruction.opcode is the given string.
 * note: only works when the current scope has a string called opcode is equal
 * to instructions[lineNum][0], assuming instructions is a char *** and
 * lineNum is an int.
 */
#ifndef opcodeIs
#define opcodeIs(opc) !strcmp(opcode, opc)

#endif /* opcodeIs */

#ifndef MAX_LETTER_CNT
#define MAX_LETTER_CNT 24
/* max number of letters per word */
#endif /* MAX_LETTER_CNT */

#ifndef MAX_WORD_CNT
#define MAX_WORD_CNT 12
/* max number of words per line */
#endif /* MAX_WORD_CNT */

#ifndef MAX_LINE_CNT
#define MAX_LINE_CNT 3072
/* max number of lines per file */
#endif /* MAX_LINE_CNT */

#ifndef MAX_FILE_SIZE
#define MAX_FILE_SIZE 884736 /*MAX_LINE_CNT * MAX_WORD_CNT * MAX_LETTER_CNT*/
/* max size in memory for a file */
#endif /* MAX_FILE_SIZE */

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;
/* ------------------- */

/* ↓ FUNCTIONS ↓ */
int isNumber(char *number);
stack_t *getTopElement();
char *getFileContents(const char *filename);
int parseInstructions(char *instructions, char ***dest);
int executeInstructions(char ***instructions);
void freeParsedInstr(char ***parsedInstructions);
void freeStack();
int push(char *n, int lineNum);
int pop(int lineNum);
int swap(int lineNum);
int add(int lineNum);
int sub(int lineNum);
void pall();
int pint(int lineNum);
/* ------------------- */

#endif /* MONTY_H */
