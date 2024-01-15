
#include <stdio.h>
#include <stdlib.h>

#include "mv_vector.h"
#include "mv_type.h"

#define MV_TYPE_IDENTIFIER  	  1
#define MV_TYPE_OPERATOR  		  2		
#define MV_TYPE_IMMEDIATE   	  3
//#define MV_TYPE_EXPRESSION_NODE   4
#define MV_TYPE_NONE 			  0


// function definition
// string length
extern len_t mv_strlen(const char* str)
{
	// Cpde
	int le = 0;

	for( le = 0; str[le] != '\0'; le++ );

	return(le);
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

//Type Checking Function
extern type_t mv_type_checking(char* ip)
{
	// Code
	if(!check_immediate(ip))
	{
		printf("IP %s is Immediate\n", ip);
		return(MV_TYPE_IMMEDIATE);			
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


static p_mv_object_t create_object(void)
{
	// Code
	p_mv_object_t obj = (p_mv_object_t)malloc(SIZE_MV_OBJECT);

	obj->object_type = 0;
	obj->object_value = NULL;

	return(obj);
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

		// printf("Obj type: %d\n", obj->object_type);
		// printf("Obj value: %p\n", obj->object_value);
		// printf("\n");

		mv_vector_push_back(object_vector, obj);

	}
	return(object_vector);

}

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

	    p_mv_vector_t token_vector = mv_strtok(input, " ");

	  	int le = 0;
	  	for(le = 0; le < mv_vector_size(token_vector); le++)
	  	{
	  		printf("Token Vector Data : { %s }\n", (char*)mv_vector_data_at(token_vector, le));
	  	}
	  	printf("\n");

	  	create_object_vector(token_vector);

	  	p_mv_vector_t object_vector = create_object_vector(token_vector);

	  	for(le = 0; le < mv_vector_size(object_vector); le++)
	  	{
	  		printf("Object Vector Data : { %p }\n", mv_vector_data_at(object_vector, le));
	  	}

	  	mv_vector_destroy(&token_vector);
	  	//printf("Token Vector Size : %zd\n", mv_vector_size(token_vector));

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

