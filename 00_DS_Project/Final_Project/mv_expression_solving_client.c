
/**
 * @File: mv_expression_solving_client.c
 * @Brief: This contains function calls made by client
 * @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 * @Date: 21-06-2024
 */

// Headers
#include <stdio.h>
#include <stdlib.h>

#include "mv_expression_solving.h"

// Global Declarations
extern p_mv_dcll_t symbol_table = NULL;
extern p_mv_dcll_t value_table = NULL;

// Entry Point Function
int main(void)
{
	// Code
	symbol_table = create_doubly_circular_list();
	value_table = create_doubly_circular_list();
 
	while(1)
	{
		// Allocating memory
		char* input = malloc(2048);
		char* str2 = "exit";

		printf("Enter expression : >");
		// User input
	   	fgets(input, 2048, stdin);

	   	input[mv_strlen(input) - 1] = '\0';

	   	if(!mv_strcmp(input, str2))
	  	{
	  		free(input);
	  		break;
	  	}

	   	// Reallocation 
	   	input = realloc(input, mv_strlen(input));

	  	// Token Vector
	    p_mv_vector_t token_vector = mv_strtok(input, " ");

	  	// Object Vector
	  	p_mv_vector_t object_vector = create_object_vector(token_vector);
	  	
	  	mv_vector_destroy(&token_vector);

	  	// Expression Stack
	  	p_mv_stack_t expression_stack = create_expression_stack(object_vector);
	
	  	mv_vector_destroy(&object_vector);

	  	// Expression_Tree
	  	p_mv_object_t ex_obj = create_expression_tree(expression_stack);

	  	// Expression Solving
	  	expression_solver(ex_obj);

	  	printf("\n");

	  	free(input);

	}
   
   exit(0);

}

