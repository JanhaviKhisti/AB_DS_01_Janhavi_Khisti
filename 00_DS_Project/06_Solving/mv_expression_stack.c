
#include <stdio.h>
#include <stdlib.h>

#include "mv_vector.h"
#include "mv_expression_stack.h"

// function definition
// string length
extern len_t mv_strlen(const char* str)
{
	// Cpde
	int le = 0;

	for( le = 0; str[le] != '\0'; le++ );

	return(le);
}

// string concate
extern ret_t mv_strconcate(char* str1, char* str2)
{
	int size1 = mv_strlen(str1);

	for(int le = 0; le < mv_strlen(str2); le++)
	{
		str1[size1] = str2[le];
		size1++;
	}

	str1[size1] = '\0';

	return(SUCCESS);
}

// string compare
extern ret_t mv_strcmp(const char* str1, const char* str2)
{
	// code
	int index = 0;

	while(1)
	{
		if( str1[index] != str2[index] )
		{
			return(FAILURE);
		}

		if( '\0' == str1[index] || '\0' == str2[index] )
			break;

		index++;
	}

	return(SUCCESS);
}

// string copy
extern char* mv_strcpy(char* dest, const char* src)
{
	// code
	int index = 0;
	for(index = 0; src[index] != '\0'; index++)
	{
		dest[index] = src[index];
	}

	dest[index] = '\0';

	return(dest);
}

// string tokanization
extern p_mv_vector_t mv_strtok(char* str, const char* delim)
{
	// code
	char* ip = NULL;
	p_mv_vector_t token_vector = NULL;

	if(str != NULL)
	{
		ip = str;
	}

	if(ip == NULL)
	{
		return(NULL);
	}

	token_vector = create_vector();
	int ole = 0;
	int ile = 0;

	for(ole = 0; ip[ole] != '\0'; ole++)
	{
		char* temp = malloc(2048);
		for(ile = 0; ip[ole] != *delim && ip[ole] != '\0' ; ile++)
		{
			temp[ile] = ip[ole];
			ole++;	
		}
		temp[ile] = '\0';
		temp = realloc(temp, mv_strlen(temp));

		//printf("Token Add : %p\n", temp);

		mv_vector_push_back(token_vector, temp);
		if(ip[ole] == '\0')
			break;
	}
	return(token_vector);
}

/*******************************************************************************/

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
		printf("IP %s is Immediate\n", ip);
		return(MV_TYPE_IMMIDIATE);			
	}
	else if(!check_identifier(ip))
	{
		printf("IP %s is Identifier\n", ip);
		return(MV_TYPE_IDENTIFIER);
	}
	else if(!check_operator(ip))
	{
		printf("IP %s is Operator\n", ip);
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
			printf("Priority -- 0\n");
			return(MV_TYPE_OPERATOR_EQUAL);
			break;

		case '+':
			printf("Priority -- 1\n");
			return(MV_TYPE_OPERATOR_ADDITION);
			break;

		case '-':
			printf("Priority -- 1\n");
			return(MV_TYPE_OPERATOR_SUBTRACTION);
			break;

		case '*':
			printf("Priority -- 2\n");
			return(MV_TYPE_OPERATOR_MULTIPLICATION);
			break;

		case '/':
			printf("Priority -- 2\n");
			return(MV_TYPE_OPERATOR_DIVISION);
			break;

		case '%':
			printf("Priority -- 2\n");
			return(MV_TYPE_OPERATOR_MODULOUS);
			break;

		default:
			return(SUCCESS);
			break;
	}
}


static ret_t get_operator_priority(p_mv_object_t obj)
{
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

void stack_print_data(data_t data)
{
	printf("|\t%d\t|\n", ((p_mv_object_t)data)->object_type);
}

static long long mv_stack_size(p_mv_stack_t pstack)
{
	return(mv_dcll_get_size(pstack->pdcll));
}

/*******************************************************************************/

static p_mv_stack_t create_expression_stack(p_mv_vector_t pvector)
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
	mv_stack_print(expression_stack, stack_print_data);

	return(expression_stack);
}

/*******************************************************************************/

static p_mv_object_t create_expression_tree(p_mv_stack_t expression_stack)
{

	while(1)
	{
		p_mv_expression_node_t ex_node = create_expression_node();

		printf(" -- Right -- \n");
		ex_node->right = mv_stack_pop(expression_stack);
		printf(" -- Operator --\n");
		ex_node->operator = mv_stack_pop(expression_stack);
		printf(" -- Left --\n");
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
static void expression_solver(p_mv_object_t object)
{
	printf("Here - 1\n");
	if( (((p_mv_expression_node_t)object->object_value)->left)->object_type == MV_TYPE_EXPRESSION_NODE)
	{
		expression_solver(((p_mv_expression_node_t)object->object_value)->left);
	} 
	printf("Here - 2\n");
	if( (((p_mv_expression_node_t)object->object_value)->right)->object_type == MV_TYPE_EXPRESSION_NODE)
	{
		expression_solver(((p_mv_expression_node_t)object->object_value)->right);
	}
	printf("Here - 3\n");
	p_mv_expression_node_t expression_node = object->object_value;
	
	char* result = NULL;
	
	p_mv_object_t temp = (((p_mv_expression_node_t)object->object_value)->operator);

	switch(operator_type(temp))
	{
		case MV_TYPE_OPERATOR_ADDITION:

			//printf("Objects = %s\n", (((p_mv_expression_node_t)object->object_value)->left)->object_value);
			//printf("Objects = %s\n", (((p_mv_expression_node_t)object->object_value)->right)->object_value);
			printf("Result = %p\n", result);

			result = Addition( ((p_mv_expression_node_t)object->object_value)->left, ((p_mv_expression_node_t)object->object_value)->right );

			//free(object->object_value);

			//free(expression_node);
			//expression_node = NULL;
			printf("Result : %p\n", result);

			printf("Result_len : %d\n",mv_strlen(result));
			printf("Result : %s\n", result);

			printf("Obj : %p\n", object);

			object->object_value = result;

			printf("Obj_val : %p\n", object->object_value);

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

			printf("Object_left = %s\n", (((p_mv_expression_node_t)object->object_value)->left)->object_value);
			printf("Object_right = %p\n", (((p_mv_expression_node_t)object->object_value)->right)->object_value);

			Assignment( ((p_mv_expression_node_t)object->object_value)->left, ((p_mv_expression_node_t)object->object_value)->right );
			
			printf("Here - 6\n");

			break;

	}


}

/*******************************************************************************/
/*******************************************************************************/

int main(void)
{
 
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

	  	for(le = 0; le < mv_vector_size(object_vector); le++)
	  	{
	  		printf("Object Vector Data : { %p }\n", mv_vector_data_at(object_vector, le));
	  	
	  	}


	  	// Operator Priority

	  	for(le = 0; le < mv_vector_size(token_vector); le++)
	  	{
	  		get_operator_priority((p_mv_object_t)mv_vector_data_at(token_vector, le));
	  	}
	  	printf("\n");


	  	// Expression Stack
	  	p_mv_stack_t expression_stack = create_expression_stack(object_vector);

	  	// Expression_Tree
	  	p_mv_object_t ex_obj = create_expression_tree(expression_stack);

	  	printf("\n");

	  	expression_solver(ex_obj);

	  	printf("\n");

	  	mv_vector_destroy(&token_vector);

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

