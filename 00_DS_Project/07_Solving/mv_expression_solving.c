
#include <stdio.h>
#include <stdlib.h>

#include "mv_expression_solving.h"


static ret_t check_immediate(char* input)
{
	// code
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

static ret_t check_identifier(char* input)
{
	// code
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

static ret_t check_operator(char* input)
{
	// code
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

/*******************************************************************************/

//Type Checking Function
extern type_t mv_type_checking(char* ip)
{
	// Code
	if(!check_immediate(ip))
	{
		//printf("IP %s is Immediate\n", ip);
		return(MV_TYPE_IMMIDIATE);			
	}
	else if(!check_identifier(ip))
	{
		//printf("IP %s is Identifier\n", ip);
		return(MV_TYPE_IDENTIFIER);
	}
	else if(!check_operator(ip))
	{
		//printf("IP %s is Operator\n", ip);
		return(MV_TYPE_OPERATOR);
	}
	else
	{
		printf("ERROR : Invalid Input\n");
	}

	return(MV_TYPE_NONE);
}

/*******************************************************************************/

static p_mv_object_t create_object(void)
{
	// Code
	p_mv_object_t obj = (p_mv_object_t)malloc(SIZE_MV_OBJECT);

	obj->object_type = 0;
	obj->object_value = NULL;

	return(obj);
}

static p_mv_expression_node_t create_expression_node(void)
{
	p_mv_expression_node_t ex_node = (p_mv_expression_node_t)malloc(SIZE_MV_EXPRESSION_NODE);

	ex_node->operator = NULL;
	ex_node->left = NULL;
	ex_node->right = NULL;

	return(ex_node);
}


extern p_mv_vector_t create_object_vector(p_mv_vector_t pvector)
{
	// code
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

static ret_t operator_type(p_mv_object_t input)
{
	char* str = input->object_value;

	switch(*str)
	{
		case '=':
			//printf("Priority -- 0\n");
			return(MV_TYPE_OPERATOR_EQUAL);
			break;

		case '+':
			//printf("Priority -- 1\n");
			return(MV_TYPE_OPERATOR_ADDITION);
			break;

		case '-':
			//printf("Priority -- 1\n");
			return(MV_TYPE_OPERATOR_SUBTRACTION);
			break;

		case '*':
			//printf("Priority -- 2\n");
			return(MV_TYPE_OPERATOR_MULTIPLICATION);
			break;

		case '/':
			//printf("Priority -- 2\n");
			return(MV_TYPE_OPERATOR_DIVISION);
			break;

		case '%':
			//printf("Priority -- 2\n");
			return(MV_TYPE_OPERATOR_MODULOUS);
			break;

		default:
			return(SUCCESS);
			break;
	}
}


extern ret_t get_operator_priority(p_mv_object_t obj)
{
	switch(operator_type(obj))
	{
		case MV_TYPE_OPERATOR_EQUAL:
			//printf("Priority -- 0\n");
			return(0);

		case MV_TYPE_OPERATOR_ADDITION:
		case MV_TYPE_OPERATOR_SUBTRACTION:
			//printf("Priority -- 1\n");
			return(1);

		case MV_TYPE_OPERATOR_MULTIPLICATION:
		case MV_TYPE_OPERATOR_DIVISION:
		case MV_TYPE_OPERATOR_MODULOUS:
			//printf("Priority -- 2\n");
			return(2);

	}
	return(0);
}

void stack_print_data(data_t data)
{
	printf("|\t%d\t|\n", ((p_mv_object_t)data)->object_type);
}

static long long mv_stack_size(p_mv_stack_t pstack)
{
	return(mv_dcll_get_size(pstack->pdcll));
}

/*******************************************************************************/

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
			
			//mv_stack_push(expression_stack, obj);

			current_operator_priority = new_operator_priority;
		}
	}
	//mv_stack_print(expression_stack, stack_print_data);

	return(expression_stack);
}

/*******************************************************************************/

extern p_mv_object_t create_expression_tree(p_mv_stack_t expression_stack)
{

	while(1)
	{
		p_mv_expression_node_t ex_node = create_expression_node();

		//printf(" -- Right -- \n");
		ex_node->right = mv_stack_pop(expression_stack);
		//printf(" -- Operator --\n");
		ex_node->operator = mv_stack_pop(expression_stack);
		//printf(" -- Left --\n");
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
extern void expression_solver(p_mv_object_t object)
{
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

		case MV_TYPE_OPERATOR_DIVISION:

			result = Division( ((p_mv_expression_node_t)object->object_value)->left, ((p_mv_expression_node_t)object->object_value)->right );

			free(expression_node);
			expression_node = NULL;

			object->object_value = result;
			object->object_type = MV_TYPE_IMMIDIATE;

			break;

		case MV_TYPE_OPERATOR_MODULOUS:

			result = Modulous( ((p_mv_expression_node_t)object->object_value)->left, ((p_mv_expression_node_t)object->object_value)->right );

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

