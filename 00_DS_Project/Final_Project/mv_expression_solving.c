
/**
 * @File: mv_expression_solving.c
 * @Brief: This contains definitions of functions declared in header file mv_expression_solving.h
 * @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 * @Date: 21-06-2024
 */

#include <stdio.h>
#include <stdlib.h>

#include "mv_expression_solving.h"

// Expresion Solving Helper Functions 

/**
 * Function Name: check_immediate
 * Function Brief: string 
 * Input Params: This function checks given string is immediate
 * Returns: Status
 *			SUCCESS if successful / FAILURE if unsuccessful
 */
static ret_t check_immediate(char* input)
{
	// Code
	char* temp = NULL;
	int index = 0;

	temp = input;

	while(1)
	{
		if(temp[index] >= 48 && temp[index] <= 57)
		{
			index++;
			if(temp[index] == '\0')
				break;
		}
		else
			return(FAILURE);
	}

	return(SUCCESS);

}

/**
 * Function Name: check_identifier
 * Function Brief: string 
 * Input Params: This function checks given string is identifier
 * Returns: Status
 *			SUCCESS if successful / FAILURE if unsuccessful
 */
static ret_t check_identifier(char* input)
{
	// Code
	char* temp = NULL;
	int index = 0;

	temp = input;

	while(1)
	{
		if( temp[index] >= 97 && temp[index] <= 122 ||
			temp[index] >= 48 && temp[index] <= 57  ||
			temp[index] >= 65 && temp[index] <= 90 )
		{
			index++;
			if(temp[index] == '\0')
				break;
		}
		else
			return(FAILURE);
	}

	return(SUCCESS);
}

/**
 * Function Name: check_operator
 * Function Brief: string 
 * Input Params: This function checks given string is operator
 * Returns: Status
 *			SUCCESS if successful / FAILURE if unsuccessful
 */
static ret_t check_operator(char* input)
{
	// Code
	char* temp = NULL;
	int index = 0;
	
	temp = input;

	while(1)
	{
		if( temp[index] == 43 || temp[index] == 45 ||
			temp[index] == 42 || temp[index] == 47 ||
			temp[index] == 37 || temp[index] == 61 )
		{
			index++;
			if(temp[index] == '\0')
				break;
		}
		else
			return(FAILURE);
	}

	return(SUCCESS);
}

/**
 * Function Name: operator_type
 * Function Brief: This function gives operator type
 * Input Params: object
 * Returns: The operator type
 */
static ret_t operator_type(p_mv_object_t input)
{
	// Code
	char* str = input->object_value;

	switch(*str)
	{
		case '=':
			return(MV_TYPE_OPERATOR_EQUAL);
			break;

		case '+':
			return(MV_TYPE_OPERATOR_ADDITION);
			break;

		case '-':
			return(MV_TYPE_OPERATOR_SUBTRACTION);
			break;

		case '*':
			return(MV_TYPE_OPERATOR_MULTIPLICATION);
			break;

		case '/':
			return(MV_TYPE_OPERATOR_DIVISION);
			break;

		case '%':
			return(MV_TYPE_OPERATOR_MODULOUS);
			break;

		default:
			return(SUCCESS);
			break;
	}
}

/**
 * Function Name: create_object
 * Function Brief: This function creates object
 * Input Params: void
 * Returns: The created object
 */
static p_mv_object_t create_object(void)
{
	// Code
	p_mv_object_t obj = (p_mv_object_t)malloc(SIZE_MV_OBJECT);

	obj->object_type = 0;
	obj->object_value = NULL;

	return(obj);
}

/**
 * Function Name: create_expression_node
 * Function Brief: This function creates expression node
 * Input Params: void
 * Returns: The expression node
 */
static p_mv_expression_node_t create_expression_node(void)
{
	// Code
	p_mv_expression_node_t ex_node = (p_mv_expression_node_t)malloc(SIZE_MV_EXPRESSION_NODE);

	ex_node->operator = NULL;
	ex_node->left = NULL;
	ex_node->right = NULL;

	return(ex_node);
}

/**
 * Function Name: mv_stack_size
 * Function Brief: This function gives size of stack
 * Input Params: stack
 * Returns: The size of stack
 */
static long long mv_stack_size(p_mv_stack_t pstack)
{
	// Code
	return(mv_dcll_get_size(pstack->pdcll));
}

/*******************************************************************************/
// Expression Solving Interface Functions

//Type Checking Function
/**
 * Function Name: mv_type_checking
 * Function Brief: This function gives type of tokenized string
 * Input Params: string
 * Returns: The type of string 
 */
extern type_t mv_type_checking(char* ip)
{
	// Code
	if(!check_immediate(ip))
	{
		return(MV_TYPE_IMMIDIATE);			
	}
	else if(!check_identifier(ip))
	{
		return(MV_TYPE_IDENTIFIER);
	}
	else if(!check_operator(ip))
	{
		return(MV_TYPE_OPERATOR);
	}
	else
	{
		printf("ERROR : Invalid Input\n");
	}

	return(MV_TYPE_NONE);
}

/*******************************************************************************/

/**
 * Function Name: create_object_vector
 * Function Brief: This function creates object vector
 * Input Params: vector 
 * Returns: vector
 */
extern p_mv_vector_t create_object_vector(p_mv_vector_t pvector)
{
	// Code
	p_mv_vector_t object_vector = NULL;
	p_mv_object_t obj = NULL;

	object_vector = create_vector();

	int le = 0;
	for(le = 0; le < mv_vector_size(pvector); le++)
	{
		char* ip = mv_vector_data_at(pvector, le);

		obj = create_object();

		obj->object_type = mv_type_checking(ip);			
		
		obj->object_value = ip;

		mv_vector_push_back(object_vector, obj);

	}	

	return(object_vector);

}

/*******************************************************************************/

/**
 * Function Name: get_operator_priority
 * Function Brief: This function gives priority of operators
 * Input Params: object
 * Returns: The priority of operator
 */
extern ret_t get_operator_priority(p_mv_object_t obj)
{
	// Code
	switch(operator_type(obj))
	{
		case MV_TYPE_OPERATOR_EQUAL:
			return(0);

		case MV_TYPE_OPERATOR_ADDITION:
		case MV_TYPE_OPERATOR_SUBTRACTION:
			return(1);

		case MV_TYPE_OPERATOR_MULTIPLICATION:
		case MV_TYPE_OPERATOR_DIVISION:
		case MV_TYPE_OPERATOR_MODULOUS:
			return(2);

	}
	
	return(0);
}

/*
void stack_print_data(data_t data)
{
	printf("|\t%d\t|\n", ((p_mv_object_t)data)->object_type);
}
*/

/*******************************************************************************/

/**
 * Function Name: create_expression_stack
 * Function Brief: This function creates expression stack of given expression
 * Input Params: vector 
 * Returns: The created stack
 */
extern p_mv_stack_t create_expression_stack(p_mv_vector_t pvector)
{
	// Code
	p_mv_stack_t expression_stack = NULL;
	p_mv_object_t obj = NULL;
	type_t temp = 0;

	expression_stack = create_stack();

	ret_t current_operator_priority = 0;

	for(int le = 0; le < mv_vector_size(pvector); le++)
	{
		obj = mv_vector_data_at(pvector, le);

		if(obj->object_type == MV_TYPE_IMMIDIATE)
		{
			mv_stack_push(expression_stack, obj);
		}
		else if(obj->object_type == MV_TYPE_IDENTIFIER)
		{
			mv_stack_push(expression_stack, obj);
		}
		else if(obj->object_type == MV_TYPE_OPERATOR)
		{
			ret_t new_operator_priority = get_operator_priority(obj);

			while(new_operator_priority < current_operator_priority)
			{ 

				// Create Expression Node
				p_mv_expression_node_t ex_node = create_expression_node();

				ex_node->right = mv_stack_pop(expression_stack);
				ex_node->operator = mv_stack_pop(expression_stack);
				ex_node->left = mv_stack_pop(expression_stack);

				// Creation of Expression Object
				p_mv_object_t ex_object = create_object();

				ex_object->object_type = MV_TYPE_EXPRESSION_NODE;
				ex_object->object_value = ex_node;

				current_operator_priority = get_operator_priority(mv_stack_peek(expression_stack));

				mv_stack_push(expression_stack, ex_object);

			}
			
			mv_stack_push(expression_stack, obj);

			current_operator_priority = new_operator_priority;
		}
	}
	//mv_stack_print(expression_stack, stack_print_data);

	return(expression_stack);
}

/*******************************************************************************/

/**
 * Function Name: create_expression_tree
 * Function Brief: This function creates expression tree of given expression
 * Input Params: stack
 * Returns: The expression node object
 */
extern p_mv_object_t create_expression_tree(p_mv_stack_t expression_stack)
{
	// Code
	while(1)
	{
		p_mv_expression_node_t ex_node = create_expression_node();

		ex_node->right = mv_stack_pop(expression_stack);
		
		ex_node->operator = mv_stack_pop(expression_stack);
		
		ex_node->left = mv_stack_pop(expression_stack);

		p_mv_object_t ex_object = create_object();

		ex_object->object_type = MV_TYPE_EXPRESSION_NODE;
		ex_object->object_value = ex_node;

		if(mv_stack_size(expression_stack))
		{
			mv_stack_push(expression_stack,ex_object);
		}
		else
		{
			return(ex_object);
		}
	}
}

/*******************************************************************************/

/**
 * Function Name: expression_solver
 * Function Brief: This function actually solves the expression
 * Input Params: object
 * Returns: void
 */
extern void expression_solver(p_mv_object_t object)
{
	// Code
	if( (((p_mv_expression_node_t)object->object_value)->left)->object_type == MV_TYPE_EXPRESSION_NODE )
	{
		expression_solver(((p_mv_expression_node_t)object->object_value)->left);
	}

	if( (((p_mv_expression_node_t)object->object_value)->right)->object_type == MV_TYPE_EXPRESSION_NODE )
	{
		expression_solver(((p_mv_expression_node_t)object->object_value)->right);
	}

	p_mv_expression_node_t expression_node = object->object_value;

	char* result = NULL;

	p_mv_object_t temp = (((p_mv_expression_node_t)object->object_value)->operator);

	switch(operator_type(temp))
	{
		case MV_TYPE_OPERATOR_ADDITION:

			result = Addition( ((p_mv_expression_node_t)object->object_value)->left, ((p_mv_expression_node_t)object->object_value)->right );

			free(expression_node);
			expression_node = NULL;
			
			object->object_value = result;
			object->object_type = MV_TYPE_IMMIDIATE;

			break;

		case MV_TYPE_OPERATOR_SUBTRACTION:

			result = Subtraction( ((p_mv_expression_node_t)object->object_value)->left, ((p_mv_expression_node_t)object->object_value)->right );

			free(expression_node);
			expression_node = NULL;

			object->object_value = result;
			object->object_type = MV_TYPE_IMMIDIATE;

			break;

		case MV_TYPE_OPERATOR_MULTIPLICATION:

			result = Multiplication( ((p_mv_expression_node_t)object->object_value)->left, ((p_mv_expression_node_t)object->object_value)->right );


			free(expression_node);
			expression_node = NULL;

			object->object_value = result;
			object->object_type = MV_TYPE_IMMIDIATE;
 	
			break;

		case MV_TYPE_OPERATOR_EQUAL:

			Assignment( ((p_mv_expression_node_t)object->object_value)->left, ((p_mv_expression_node_t)object->object_value)->right );
			break;

	}
}

/*******************************************************************************/

