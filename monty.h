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
#define MAX_LETTER_CNT 16

#endif /* MAX_LETTER_CNT */

#ifndef MAX_WORD_CNT
#define MAX_WORD_CNT 4

#endif /* MAX_WORD_CNT */

#ifndef MAX_LINE_CNT
#define MAX_LINE_CNT 1024

#endif /* MAX_LINE_CNT */

#ifndef MAX_FILE_SIZE
#define MAX_FILE_SIZE 49152 /*MAX_LINE_CNT * MAX_WORD_CNT * MAX_LETTER_CNT*/

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
stack_t *getTopElement(stack_t *stack);
char *getFileContents(const char *filename);
int parseInstructions(char *instructions, char ***dest);
int executeInstructions(char ***instructions, stack_t *stack);
void freeParsedInstr(char ***parsedInstructions);
void freeStack(stack_t *stack);
int push(char *n, int lineNum, stack_t **stack);
void pall(int lineNum, stack_t *stack);
/* ------------------- */

#endif /* MONTY_H */
