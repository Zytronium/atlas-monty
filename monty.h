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
char *get_file_contents(const char *filename);
void parse_instructions(char *instructions, char ***dest);
int execute_instructions(char ***instructions, stack_t *stack);
void push(char *n, int lineNum, stack_t *stack);
void pall(int lineNum, stack_t *stack);
/* ------------------- */

#endif /* MONTY_H */
