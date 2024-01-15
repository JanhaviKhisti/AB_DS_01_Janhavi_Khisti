

#include <stdio.h>
#include <stdlib.h>

#include "mv_expression_solving.h"

extern p_mv_dcll_t symbol_table = NULL;
extern p_mv_dcll_t value_table = NULL;

int main(void)
{
	symbol_table = create_doubly_circular_list();
	value_table = create_doubly_circular_list();
 
	while(1)
	{
		// allocating memory
		char* input = malloc(2048);
		char* str2 = "exit";

		printf("Enter input : >");
		// user input
	   	fgets(input, 2048, stdin);

	   	input[mv_strlen(input) - 1] = '\0';

	   	// reallocation 
	   	input = realloc(input, mv_strlen(input));

	  	printf("String is : %s\n", input);
	  	printf("\n");

	  	// Token Vector

	    p_mv_vector_t token_vector = mv_strtok(input, " ");

	  	int le = 0;
	  	for(le = 0; le < mv_vector_size(token_vector); le++)
	  	{
	  		printf("Token Vector Data : { %s }\n", (char*)mv_vector_data_at(token_vector, le));
	  	
	  	}
	  	printf("\n");


	  	// Object Vector

	  	p_mv_vector_t object_vector = create_object_vector(token_vector);

	  	// for(le = 0; le < mv_vector_size(object_vector); le++)
	  	// {
	  	// 	printf("Object Vector Data : { %p }\n", mv_vector_data_at(object_vector, le));
	  	
	  	// }

	  	// Operator Priority

	  	// for(le = 0; le < mv_vector_size(token_vector); le++)
	  	// {
	  	// 	get_operator_priority((p_mv_object_t)mv_vector_data_at(token_vector, le));

	  	// }
	  	// printf("\n");


	  	// Expression Stack
	  	p_mv_stack_t expression_stack = create_expression_stack(object_vector);

	  	// Expression_Tree
	  	p_mv_object_t ex_obj = create_expression_tree(expression_stack);

	  	// printf("\n");

	  	expression_solver(ex_obj);

	  	printf("\n");

	  	if(!mv_strcmp(input, str2))
	  	{
	  		free(input);
	  		break;
	  	}
	  	// free memory
	  	free(input);

	}
   
   exit(0);

}

