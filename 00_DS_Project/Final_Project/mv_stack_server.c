
/**
 * @File: mv_stack_server.c
 * @Brief: This contains definitions of functions declared in header file mv_stack.h
 * @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 * @Date: 20-06-2024
 */

//	Headers
#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_stack.h"

// Function Declaration
static	ret_t	error_checking(	const int 	assert_condition,
								const char* assert_condition_str,
								const char*	file_name,
								const long	line_no,
								const int 	error_condition,
								const char*	error_str);

// Macros
#define		ERROR_CHECKING( assert_condition, error_condition, error_str )		(											\
																					error_checking( assert_condition,		\
																									#assert_condition,		\
																									__FILE__,				\
																									__LINE__,				\
																									error_condition,		\
																									error_str )				\
																				)

// Stack Helper Functions

/**
 * Function Name: Xmalloc
 * Function Brief: This function will allocate a memory of 'nr_of_bytes' size
 * Input Params: nr_of_bytes
 * Returns: The pointer to the memory dynamically allocated of 'nr_of_bytes' size
 */
static	void	*Xmalloc(size_t nr_of_bytes)
{
	// Code
	void* p = malloc(nr_of_bytes);

	ERROR_CHECKING(	1, 
					NULL == p,
					"ERROR: Out Of Memory.\n");

	return(p);
}

/**
 * Function Name: error_checking
 * Function Brief: This function will check error and either print erroe message of will do assertion
 * Input Params: 1) Assert Condition
 *               2) String of Assert condition
 *               3) File where assertion occured
 *               4) Line no where assertion occured
 *               5) Error Condition
 *               6) Error Message
 * Returns: Status of the error / asssert checking
 */
static	ret_t	error_checking(	const int 	assert_condition,
								const char* assert_condition_str,
								const char*	file_name,
								const long	line_no,
								const int 	error_condition,
								const char*	error_str)
{
	// Code

	#ifdef	MV_DEBUG
		//	Assertion
		if( !assert_condition )
		{
			fprintf(stdout, 
					"Assertion Filed: %s, File: %s, Line #: %ld\n", 
					assert_condition_str,
					file_name,
					line_no);
			return(FAILURE);
		}
	#else
		// Error Checking
		if( error_condition )
		{
			if( NULL != error_str )
			{
				fprintf(stderr, error_str);
				return(FAILURE);
			}
		}
	#endif

	return(SUCCESS);
}


//	Stack Interface Functions

// Stack Creation Function
/**
 * Function Name: create_stack
 * Function Brief: This function creates a stack using a doubly linked list implementation and returns a pointer to it
 * Input Params: none
 * Returns: Pointer to the created stack.
 */
extern	p_mv_stack_t 	create_stack(void)
{
	//	Code
	p_mv_stack_t pstack = Xmalloc(SIZE_STACK);
	ERROR_CHECKING( NULL != pstack,
					1,
					NULL);

	pstack->pdcll = create_doubly_circular_list();
	ERROR_CHECKING( NULL != pstack->pdcll,
					1,
					NULL );

	return(pstack);
}

// Stack Insertion Function
/**
 * Function Name: mv_stack_push
 * Function Brief: This function pushes data onto the top of the stack.
 * Input Params: 1) Pointer to the stack
 *				 2) Data to be pushed onto the stack
 * Returns: Status of push operation
 *			SUCCESS if successful / FAILURE if unsuccessful
 */
extern	ret_t	mv_stack_push(p_mv_stack_t pstack, data_t data)
{
	//	Code
	ERROR_CHECKING( NULL != pstack,
					NULL == pstack,
					"ERROR: Stack not found.\n" );

	return( mv_dcll_insert_back(pstack->pdcll, data) );
}

// Stack Removal Function
/**
 * Function Name: mv_stack_pop
 * Function Brief: This function pops data from top of stack
 * Input Params: Pointer to the stack
 * Returns: The popped data from the top of the stack
 */
extern	data_t	mv_stack_pop(p_mv_stack_t pstack)
{
	// Code
	ERROR_CHECKING( NULL != pstack,
					NULL == pstack,
					"ERROR: Stack Not found.\n" );

	return( mv_dcll_remove_back(pstack->pdcll) );
}

// Stack getter Function
/**
 * Function Name: mv_stack_peek
 * Function Brief: This function gives data at top of stack
 * Input Params: Pointer to the stack
 * Returns: The data at the top of the stack
 */
extern	data_t	mv_stack_peek(p_mv_stack_t pstack)
{
	//	Code
	ERROR_CHECKING( NULL != pstack,
					NULL == pstack,
					"ERROR: Stack Not found");

	data_t to_return_data = mv_dcll_get_tail( pstack->pdcll);

	return(to_return_data);
}

// Stack Print Function
/**
 * Function Name: mv_stack_print
 * Function Brief: This function prints the content of the stack
 * Input Params: Pointer to the stack
 * Returns: None
 */
extern	void 	mv_stack_print(p_mv_stack_t pstack, void (*pPrintDataFunc) (data_t) )
{
	//	Code
	ret_t status = 	ERROR_CHECKING( NULL != pstack,
									NULL == pstack,
									"ERROR: Stack not found.\n" );

	if( FAILURE == status )
		return;

	status = ERROR_CHECKING(NULL != pPrintDataFunc,
							NULL == pPrintDataFunc,
							"ERROR: Print Function Not Found.\n");

	if( FAILURE == status ) 
		return;

	fprintf(stdout, "\n STACK:\n");

	fprintf(stdout, "|\tTOP\t|\n\n");

	mv_dcll_print_reverse(pstack->pdcll, pPrintDataFunc);

	fprintf(stdout, "\n|\tSTART\t|\n\n\n");
}

// Stack Destroy Function
/**
 * Function Name: mv_stack_destroy
 * Function Brief: This function destroys the stack and free its memory
 * Input Params: Pointer to the pointer of the stack
 * Returns: Status 
 *			SUCCESS if successful / FAILURE if unsuccessful
 */
extern	ret_t	mv_stack_destroy(pp_mv_stack_t ppstack)
{
	// Code
	p_mv_stack_t pstack = *ppstack;

	ERROR_CHECKING( NULL != pstack,
					NULL == pstack,
					"ERROR: Stack not found.\n" );

	//	release vector
	mv_dcll_destroy( &(pstack->pdcll));

	if( pstack )
	{
		free(pstack);
		pstack = NULL;
	}

	*ppstack = NULL;

	return(SUCCESS);
}

