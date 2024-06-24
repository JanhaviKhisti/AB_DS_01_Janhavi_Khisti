
/**
 * @File: mv_operation_solving.c
 * @Brief: This contains implementation of operations to be performed
 * @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 * @Date: 21-06-2024
 */

// Headers
#include <stdio.h>
#include <stdlib.h>

#include "mv_expression_solving.h"

// Global Declarations
extern p_mv_dcll_t symbol_table;
extern p_mv_dcll_t value_table;

// Operation Solving Helper Functions

/**
 * Function Name: Xmalloc
 * Function Brief: This function will allocate a memory of 'no_of_bytes' size
 * Input Params: no_of_bytes
 * Returns: The pointer to the memory dynamically allocated of 'no_of_bytes' size
 */
static void* xmalloc(size_t no_of_bytes)
{
	// Code
	void* p = malloc(no_of_bytes);

	if( NULL == p)
	{
		fprintf(stderr, "ERROR: Out Of Memory\n");
		return(NULL);
	}

	return(p);
}

/**
 * Function Name: create_value_object
 * Function Brief: This function creates value objects
 * Input Params: None
 * Returns: The value object
 */
static p_mv_value_object_t create_value_object()
{
	// Code
	p_mv_value_object_t new_obj = (p_mv_value_object_t)xmalloc(SIZE_MV_VALUE_OBJECT);

	if(NULL == new_obj)
	{
		fprintf(stderr, "ERROR : Out of Memory\n");
		return(NULL);
	}

	new_obj->type = NO;
	new_obj->data = NULL;
	new_obj->no_of_ref = 0;

	return(new_obj);
}

/**
 * Function Name: create_symbol_object
 * Function Brief: This function creates symbol object
 * Input Params: None
 * Returns: The symbol object
 */
static p_mv_symbol_object_t create_symbol_object()
{
	// Code
	p_mv_symbol_object_t new_obj = (p_mv_symbol_object_t)xmalloc(SIZE_MV_SYMBOL_OBJECT);

	if(NULL == new_obj)
	{
		fprintf(stderr, "ERROR : Out of Memory\n");
		return(NULL);
	}

	new_obj->data = NULL;
	new_obj->pvalobj = NULL;

	return(new_obj);
}

/**
 * Function Name: locate_value_object
 * Function Brief: This function locates value object in value table
 * Input Params: data
 * Returns: The value object
 */
static p_mv_value_object_t locate_value_object(data_t valdata)
{
	// Code
	p_node_t prunner = value_table->p_head->p_next;

	while(prunner != value_table->p_head)
	{
		if( 1 == mv_strcmp2(((p_mv_value_object_t)prunner->key)->data, valdata))
		{
			return((p_mv_value_object_t)prunner->key);
		}

		prunner = prunner->p_next;
	}

	return(NULL);
}

/**
 * Function Name: locate_symbol_object
 * Function Brief: This function locates the symbol object in symbol table
 * Input Params: data
 * Returns: The symbol object
 */
static p_mv_symbol_object_t locate_symbol_object(data_t symdata)
{
	// Code
	p_node_t prunner = symbol_table->p_head->p_next;

	while(prunner != symbol_table->p_head)
	{

		if( 1 == mv_strcmp2(((p_mv_symbol_object_t)prunner->key)->data, symdata))
		{
			return(((p_mv_symbol_object_t)prunner->key));
		}

		prunner = prunner->p_next;
	}

	return(NULL);
}

/**
 * Function Name: mv_str_compare_digits
 * Function Brief: This function compares the digits in two given strings
 * Input Params: 1) string1
 *				 2) string2
 * Returns: Status
 */
static ret_t mv_str_compare_digits(char* str1, char* str2)
{
	// Code
	int le = 0;

	while(str1[le] != '\0' && str2[le] != '\0')
	{
		if(str2[le] > str1[le])
			return(1);
		else if(str2[le] < str1[le])
			return(0);

		le++;
	}

	return(0);
}

/**
 * Function Name: printtb
 * Function Brief: this function prints symbol objects 
 * Input Params: data
 * Returns: void
 */
static void printtb(data_t data)
{
	// Code
	printf("  %s", (char*)((p_mv_symbol_object_t)data)->data);
}

/**
 * Function Name: print
 * Function Brief: This function prints value objects 
 * Input Params: data
 * Returns: void
 */
static void print(data_t data)
{
	// Code
	printf("  %s", (char*)((p_mv_value_object_t)data)->data);
}

/**
 * Function Name: generic_addition
 * Function Brief: This function contains generic implementation of addition operation
 * Input Params: 1) string1
 *				 2) string2
 * Returns: string (answer)
 */
static char* generic_addition(char* str1, char* str2)
{
	// Code
	long long len1 = mv_strlen(str1);
	long long len2 = mv_strlen(str2);

	char* temp = NULL;
	long long temp_len = 0;
	char* new_str = (char*)malloc(len1 + len2);
	memset(new_str, 0, len1 + len2);

	if(mv_strlen(str1) < mv_strlen(str2))
	{
		temp = str1;
		str1 = str2;
		str2 = temp;

		temp_len = len1;
		len1 = len2;
		len2 = temp_len;
	}

	mv_strrev(str1);
	mv_strrev(str2);

	int carry = 0;
	int le = 0;
	for( le = 0; le < len2; ++le )
	{
		int result = (str1[le]-'0') + (str2[le]-'0') + carry;

		int sum = result % 10;
		carry = result / 10;

		new_str[le] = (char)(sum + '0');
	}

	for(le; le < len1; ++le)
	{
		int result = (str1[le]-'0') + carry;

		int sum = result % 10;
		carry = result / 10;
		new_str[le] = (char)(sum + '0');
	}

	new_str[le] = '\0';
	new_str = (char*) realloc(new_str, mv_strlen(new_str)+1);
	mv_strrev(new_str);

	return(new_str);

}

/*******************************************************************************/

// Operation Solving Interface Functions

/**
 * Function Name: Addition
 * Function Brief: This function performs addition operation
 * Input Params: 1) object1
 *				 2) object2
 * Returns: answer string
 */
extern char* Addition(p_mv_object_t object1, p_mv_object_t object2)
{
	// Code
	char* str_obj1 = object1->object_value;
	char* str_obj2 = object2->object_value;

	char* new_str = (char*)malloc(1024);
	memset(new_str, 0, 1024);

	new_str = generic_addition(str_obj1, str_obj2);

	free(object1->object_value);
	object1->object_value = NULL;

	free(object1);
	object1 = NULL;

	free(object2->object_value);
	object2->object_value = NULL;

	free(object2);
	object2 = NULL;

	return(new_str);

} 

/**
 * Function Name: Subtraction
 * Function Brief: This function performs subtraction operation
 * Input Params: 1) object1
 *				 2) object2
 * Returns: answer string
 */
extern char* Subtraction(p_mv_object_t object1, p_mv_object_t object2)
{
	// Code
	char* temp = NULL;
	char* str_obj1 = object1->object_value;
	char* str_obj2 = object2->object_value;

	char* new_str = (char*)malloc(1024);
	memset(new_str, 0, 1024);

	char* concate = (char*)malloc(1024);
	memset(concate, 0, sizeof(concate));

	if(mv_strlen(str_obj2) > mv_strlen(str_obj1))
	{
		temp = str_obj2;
		str_obj2 = str_obj1;
		str_obj1 = temp;

		concate[0] = '-';
	}
	else if(mv_strlen(str_obj1) == mv_strlen(str_obj2))
	{
		if( 1 == mv_str_compare_digits(str_obj1, str_obj2))
		{
			temp = str_obj1;
			str_obj1 = str_obj2;
			str_obj2 = temp;

			concate[0] = '-';
		}
	}

	int len1 = mv_strlen(str_obj1);
	int len2 = mv_strlen(str_obj2);
	
	mv_strrev(str_obj1);
	mv_strrev(str_obj2);

	int borrow = 0;

	for(int le = 0; le < len2; le++)
	{
		int sub = ((str_obj1[le]-'0') - (str_obj2[le]-'0') - borrow);	
		borrow = 0;
		
		if( sub < 0 )
		{
			borrow = 1;
			sub = sub + 10;
		}

		new_str[le] = (sub+'0');
	}

	for(int le = len2; le < len1; le++)
	{
		int sub = ((str_obj1[le]-'0') - borrow);
		borrow = 0;			
			
		if( sub < 0 )
		{
			borrow = 1;
			sub = sub + 10;
		}

		new_str[le] = (sub+'0');
	}

	new_str[len1] = '\0';

	new_str = (char*)realloc(new_str, mv_strlen(new_str));

	mv_strrev(new_str);
	mv_strconcate(concate, new_str);

	concate = (char*)realloc(concate, mv_strlen(concate));
	
	free(object1->object_value);
	object1->object_value = NULL;

	free(object1);
	object1 = NULL;

	free(object2->object_value);
	object2->object_value = NULL;

	free(object2);
	object2 = NULL;

	free(new_str);

	return(concate);
} 

/**
 * Function Name: Multiplication
 * Function Brief: This function performs multiplication operation
 * Input Params: 1) object1
 *				 2) object2
 * Returns: answer string
 */
extern char* Multiplication(p_mv_object_t object1, p_mv_object_t object2)
{
	// Code
	char* temp = NULL;
	char* temp_str1 = NULL;
	char* temp_str2 = NULL;
	p_mv_vector_t mul_result_vector = NULL;

	char* str_obj1 = object1->object_value;
	char* str_obj2 = object2->object_value;

	char* new_str = NULL;
	
	mul_result_vector = create_vector();

	if(mv_strlen(str_obj1) > mv_strlen(str_obj2))
	{
		temp = str_obj1;
		str_obj1 = str_obj2;
		str_obj2 = temp;
	}

	int len1 = mv_strlen(str_obj1);	

	int len2 = mv_strlen(str_obj2);
	
	mv_strrev(str_obj1);
	mv_strrev(str_obj2);

	int carry = 0;

	for(int ole = 0; ole < len1; ole++)
	{
		char* result = (char*)malloc(1024);
		memset(result, 0, 1024);

		carry = 0;
		int n1 = (str_obj1[ole]-'0');

		if( ole > 0)
		{
			for(int le = 0; le < ole; le++)
			{
				result[le] = '0';
			}
		}
	
		for(int ile = 0; ile < len2; ile++)
		{
			int n2 = (str_obj2[ile]-'0');

			int mul = n1 * n2 + carry;
			carry = 0;

			if( mul > 9 )
			{
				carry = mul/10;
				mul = mul %10;
			}

			result[ole+ile] = (mul+'0');
		}

		if(carry)
		{
			result[ole+len2] = (carry+'0');
			result[ole+len2+1] = '\0';

		}
		else
		{
			result[ole+len2] = '\0';

		} 

		result = (char*)realloc(result, mv_strlen(result)+1);

		mv_vector_push_back(mul_result_vector, result);
		//printf("\n");
	}

	for(int le = mv_vector_size(mul_result_vector); le > 0; le--)
	{
		char* new_str = (char*)malloc(1024);
		memset(new_str, 0, 1024);

		if( 1 == (mv_vector_size(mul_result_vector)))
			break;

		temp_str1 = mv_vector_pop_back(mul_result_vector);
		mv_strrev(temp_str1);

		temp_str2 = mv_vector_pop_back(mul_result_vector);
		mv_strrev(temp_str2);
		
		new_str = generic_addition(temp_str1, temp_str2);
		
		free(temp_str1);
		free(temp_str2);

		new_str = (char*)realloc(new_str, mv_strlen(new_str));
		mv_strrev(new_str);

		mv_vector_push_back(mul_result_vector, new_str);
	}

	new_str = mv_vector_pop_back(mul_result_vector);
	mv_strrev(new_str);

	new_str = (char*)realloc(new_str, mv_strlen(new_str));
	
	free(object1->object_value);
	object1->object_value = NULL;

	free(object1);
	object1 = NULL;

	free(object2->object_value);
	object2->object_value = NULL;

	free(object2);
	object2 = NULL;

	mv_vector_destroy(&mul_result_vector);

	return(new_str);
} 

/**
 * Function Name: Assignment
 * Function Brief: This function performs assignment operation
 * Input Params: 1) object1
 *				 2) object2
 * Returns: void
 */
extern void Assignment(p_mv_object_t object1, p_mv_object_t object2)
{
	// Code
	char* str_obj1 = object1->object_value;
	char* str_obj2 = object2->object_value;
	p_mv_value_object_t valobj = NULL;
	p_mv_symbol_object_t esymobj = NULL;
	p_mv_value_object_t stored = NULL;

	if( object2->object_type == MV_TYPE_IMMIDIATE )
	{

		valobj = locate_value_object(str_obj2);

		if(valobj)
		{
			valobj->no_of_ref = valobj->no_of_ref + 1;
		}
		else
		{
			valobj = create_value_object();

			valobj->type = MV_TYPE_INT;
			valobj->data = str_obj2;
			valobj->no_of_ref = 1;

			printf("\n%s\n", str_obj2);

			mv_dcll_insert_back(value_table, valobj);
		}
	}
	else if( object2->object_type == MV_TYPE_IDENTIFIER )
	{
		esymobj = locate_symbol_object(str_obj2);

		if(esymobj)
		{
			stored = esymobj->pvalobj;

			esymobj = locate_symbol_object(str_obj1);

			if(esymobj)
			{
				esymobj->pvalobj = stored;
				return;
			}
			else
			{
				esymobj = create_symbol_object();
				esymobj->data = (data_t)str_obj1;
				esymobj->pvalobj = stored;

				mv_dcll_insert_back(symbol_table, esymobj);
				return;
			}
		}
		else
		{
			fprintf(stderr, "ERROR : Undefined Identifier '%s' \n", str_obj2);
			return;
		}
	}

	// For Symbol Object
	if( object1->object_type == MV_TYPE_IDENTIFIER )
	{
		esymobj = locate_symbol_object(str_obj1);

		if(esymobj)
		{
			data_t data = ((p_mv_value_object_t)esymobj)->data;

			((p_mv_value_object_t)esymobj->data)->no_of_ref = ((p_mv_value_object_t)esymobj->data)->no_of_ref - 1;

			if(((p_mv_value_object_t)esymobj->data)->no_of_ref == 0)
			{
				free(((p_mv_value_object_t)esymobj)->data);
				((p_mv_value_object_t)esymobj)->data = NULL;
 
			}

			esymobj->data = (data_t)str_obj1;
			esymobj->pvalobj = valobj;
		}
		else
		{
			esymobj = create_symbol_object();
			esymobj->data = str_obj1;
			esymobj->pvalobj = valobj;

			mv_dcll_insert_back(symbol_table, esymobj);
		}
	}
	else
	{
		fprintf(stderr, "ERROR : lvalue required\n");
		return;
	}

	//mv_dcll_print_forward(symbol_table, printtb);

	//mv_dcll_print_forward(value_table, print);

}

