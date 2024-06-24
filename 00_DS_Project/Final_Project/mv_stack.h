
/**
 * @File: mv_stack.h
 * @Brief: This contains function declarations for mv_stack
 * @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 * @Date: 21-06-2024
 */

#ifndef  	_MV_STACK_H
#define  	_MV_STACK_H

// Header File
#include 	"mv_dcll.h"

// Macros
#ifndef  	SUCCESS
#define  	SUCCESS  	0
#endif

#ifndef  	FAILURE
#define  	FAILURE  	1
#endif

// Type Definitions

struct mv_stack;  	// Declaration

typedef  	struct mv_stack  	mv_stack_t;
typedef  	struct mv_stack*  	p_mv_stack_t;
typedef  	struct mv_stack** 	pp_mv_stack_t;

typedef  	void*  	data_t;
typedef  	int  	ret_t;

// Struct type Definition
struct mv_stack
{
	p_mv_dcll_t  	pdcll;
};
#define  	SIZE_STACK  	(sizeof(mv_stack_t))

// Stack Interface Functions

// Stack Creation Function
/**
 * Function Name: create_stack
 * Function Brief: This function creates a stack using a doubly linked list implementation and returns a pointer to it
 * Input Params: none
 * Returns: Pointer to the created stack.
 */
extern  	p_mv_stack_t  	create_stack(void);

// Stack Insertion Function
/**
 * Function Name: mv_stack_push
 * Function Brief: This function pushes data onto the top of the stack.
 * Input Params: 1) Pointer to the stack
 *				 2) Data to be pushed onto the stack
 * Returns: Status of push operation
 *			SUCCESS if successful / FAILURE if unsuccessful
 */
extern  ret_t  	mv_stack_push(p_mv_stack_t pstack, data_t data);

// Stack Removal Function
/**
 * Function Name: mv_stack_pop
 * Function Brief: This function pops data from top of stack
 * Input Params: Pointer to the stack
 * Returns: The popped data from the top of the stack
 */
extern  data_t  mv_stack_pop(p_mv_stack_t pstack);

// Stack getter Function
/**
 * Function Name: mv_stack_peek
 * Function Brief: This function gives data at top of stack
 * Input Params: Pointer to the stack
 * Returns: The data at the top of the stack
 */
extern  data_t  mv_stack_peek(p_mv_stack_t pstack);

// Stack Print Function
/**
 * Function Name: mv_stack_print
 * Function Brief: This function prints the content of the stack
 * Input Params: Pointer to the stack
 * Returns: None
 */
extern  void  	mv_stack_print(p_mv_stack_t pstack, void (*pPrintDataFunc)(data_t) );

// Stack Destroy Function
/**
 * Function Name: mv_stack_destroy
 * Function Brief: This function destroys the stack and free its memory
 * Input Params: Pointer to the pointer of the stack
 * Returns: Status 
 *			SUCCESS if successful / FAILURE if unsuccessful
 */
extern  ret_t  	mv_stack_destroy(pp_mv_stack_t ppstack);

#endif	/* _MV_STACK_H */


