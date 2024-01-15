

#include <stdio.h>
#include <stdlib.h>

#include "mv_expression_solving.h"

extern p_mv_dcll_t symbol_table;
extern p_mv_dcll_t value_table;

static void* xmalloc(size_t no_of_bytes)
{
	void* p = malloc(no_of_bytes);

	if( NULL == p)
	{
		fprintf(stderr, "ERROR: Out Of Memory\n");
		return(NULL);
	}

	return(p);
}

static p_mv_value_object_t create_value_object()
{
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

static p_mv_symbol_object_t create_symbol_object()
{
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

static p_mv_value_object_t locate_value_object(data_t valdata)
{
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

static p_mv_symbol_object_t locate_symbol_object(data_t symdata)
{
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

static ret_t mv_str_compare_digits(char* str1, char* str2)
{
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


static void printtb(data_t data)
{
	printf("{%s}-", (char*)((p_mv_symbol_object_t)data)->data);
}

static void print(data_t data)
{
	printf("{%s}-", (char*)((p_mv_value_object_t)data)->data);
}

static char* generic_addition(char* str1, char* str2)
{
	char* temp = NULL;
	char* new_str = (char*)malloc(1024);
	memset(new_str, 0, 1024);

	if(mv_strlen(str1) > mv_strlen(str2))
	{
		temp = str1;
		str1 = str2;
		str2 = temp;
	}

	int len1 = mv_strlen(str1);
	int len2 = mv_strlen(str2);

	mv_strrev(str1);
	mv_strrev(str2);

	int carry = 0;

	for(int le = 0; le < len1; le++)
	{
		int sum = ((str1[le]-'0') + (str2[le]-'0') + carry);	
		carry = 0;
		
		if( sum > 9 )
		{
			carry = 1;
			sum = sum - 10;
		}

		new_str[le] = (sum+'0');
	}	

	for(int le = len1; le < len2; le++)
	{
		int sum = ((str2[le]-'0') + carry);
		carry = 0;			
			
		if( sum > 9 )
		{
			carry = 1;
			sum = sum - 10;
		}

		new_str[le] = (sum+'0');
	}
	
	if(carry)
	{
		new_str[len2] = (carry+'0');
	}

	new_str[len2+1] = '\0';

	mv_strrev(new_str);

	new_str = (char*)realloc(new_str, mv_strlen(new_str)+1);

	return(new_str);

}

/*******************************************************************************/

extern char* Addition(p_mv_object_t object1, p_mv_object_t object2)
{
	char* str_obj1 = object1->object_value;
	char* str_obj2 = object2->object_value;

	// char* temp = NULL;
	char* new_str = (char*)malloc(1024);
	memset(new_str, 0, 1024);

	new_str = generic_addition(str_obj1, str_obj2);

	printf("Str : %s\n", new_str);

	new_str = (char*)realloc(new_str, mv_strlen(new_str)+1);

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

extern char* Subtraction(p_mv_object_t object1, p_mv_object_t object2)
{
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

	mv_strrev(new_str);

	new_str = (char*)realloc(new_str, mv_strlen(new_str)+1);

	mv_strconcate(concate, new_str);

	concate = (char*)realloc(concate, mv_strlen(concate)+1);

	printf("Str = %s\n", concate);
	
	free(object1->object_value);
	object1->object_value = NULL;

	free(object1);
	object1 = NULL;

	free(object2->object_value);
	object2->object_value = NULL;

	free(object2);
	object2 = NULL;

	return(concate);

} 


extern char* Multiplication(p_mv_object_t object1, p_mv_object_t object2)
{
	char* temp = NULL;
	char* temp_str1 = NULL;
	char* temp_str2 = NULL;
	p_mv_vector_t mul_result_vector = NULL;

	char* str_obj1 = object1->object_value;
	printf("str1 : %s\n", str_obj1);

	char* str_obj2 = object2->object_value;
	printf("str2 : %s\n", str_obj2);

	char* new_str = (char*)malloc(1024);
	memset(new_str, 0, 1024);

	mul_result_vector = create_vector();

	if(mv_strlen(str_obj1) > mv_strlen(str_obj2))
	{
		temp = str_obj1;
		str_obj1 = str_obj2;
		str_obj2 = temp;
	}

	int len1 = mv_strlen(str_obj1);
	//printf("len1 = %d\n", len1);

	int len2 = mv_strlen(str_obj2);
	//printf("len2 = %d\n", len2);

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

	}

	printf("Vector_Size : %zd\n", mv_vector_size(mul_result_vector));

	for(int le = 0; le < mv_vector_size(mul_result_vector); le++)
	{
	 	printf("Result Vector Data_1 : { %s }\n", (char*)mv_vector_data_at(mul_result_vector, le));
	  		
	}

	for(int le = mv_vector_size(mul_result_vector); le > 0; le--)
	{
		char* new_str = (char*)malloc(1024);
		memset(new_str, 0, 1024);

		if( 1 == (mv_vector_size(mul_result_vector)))
			break;

		temp_str1 = mv_vector_pop_back(mul_result_vector);
		mv_strrev(temp_str1);
		printf("temp_str1: %s\n", temp_str1);

		temp_str2 = mv_vector_pop_back(mul_result_vector);
		mv_strrev(temp_str2);
		printf("temp_str2: %s\n\n", temp_str2);

		new_str = generic_addition(temp_str1, temp_str2);

		mv_strrev(new_str);
		new_str = (char*)realloc(new_str, mv_strlen(new_str));

		mv_vector_push_back(mul_result_vector, new_str);

	}

	for(int le = 0; le < mv_vector_size(mul_result_vector); le++)
	{
	 	printf("Result Vector Data_2 : { %s }\n", (char*)mv_vector_data_at(mul_result_vector, le));
	  		
	}

	new_str = mv_vector_pop_back(mul_result_vector);
	mv_strrev(new_str);

	new_str = (char*)realloc(new_str, mv_strlen(new_str));

	printf("Str = %s\n", new_str);
	
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


extern char* Division(p_mv_object_t object1, p_mv_object_t object2)
{
	char* str_obj1 = object1->object_value;
	char* str_obj2 = object2->object_value;

	char* str = (char*)malloc(1024);

	memset(str, 0, 1024);

	mv_strcpy(str, "Div(");
	mv_strconcate(str, str_obj1);
	mv_strconcate(str, ", ");
	mv_strconcate(str, str_obj2);
	mv_strconcate(str, ")");

	str = (char*)realloc(str, mv_strlen(str));

	printf("Str = %s\n", str);
	
	free(object1->object_value);
	object1->object_value = NULL;

	free(object1);
	object1 = NULL;

	free(object2->object_value);
	object2->object_value = NULL;

	free(object2);
	object2 = NULL;

	return(str);

} 


extern char* Modulous(p_mv_object_t object1, p_mv_object_t object2)
{
	char* str_obj1 = object1->object_value;
	char* str_obj2 = object2->object_value;

	char* str = (char*)malloc(1024);

	memset(str, 0, 1024);

	mv_strcpy(str, "Mod(");
	mv_strconcate(str, str_obj1);
	mv_strconcate(str, ", ");
	mv_strconcate(str, str_obj2);
	mv_strconcate(str, ")");

	str = (char*)realloc(str, mv_strlen(str));

	printf("Str = %s\n", str);
	
	free(object1->object_value);
	object1->object_value = NULL;

	free(object1);
	object1 = NULL;

	free(object2->object_value);
	object2->object_value = NULL;

	free(object2);
	object2 = NULL;

	return(str);

} 


extern void Assignment(p_mv_object_t object1, p_mv_object_t object2)
{
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

	// For symbol object
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

	mv_dcll_print_forward(symbol_table, printtb);

	mv_dcll_print_forward(value_table, print);

	return;
	//printf("Assignment(%s, %s)\n", str_obj1, str_obj2);

}

