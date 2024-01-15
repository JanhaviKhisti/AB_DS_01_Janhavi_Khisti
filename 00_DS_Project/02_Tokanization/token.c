
#include <stdio.h>
#include <stdlib.h>

#include "mv_vector.h"

#define SUCCESS  0
#define FAILURE  1

// type definition
typedef int ret_t;
typedef int len_t;


// function declaration
// string length
len_t mv_strlen(const char* str);

// string compare
ret_t mv_strcmp(const char* str1, const char* str2);

// string copy
char* mv_strcpy(char* dest, const char* src);

// string tokanization
p_mv_vector_t mv_strtok(char* str, const char* delim);


// function definition
// string length
len_t mv_strlen(const char* str)
{
	// Cpde
	int le = 0;

	for( le = 0; str[le] != '\0'; le++ );

	return(le);
}

// string compare
ret_t mv_strcmp(const char* str1, const char* str2)
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
char* mv_strcpy(char* dest, const char* src)
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
p_mv_vector_t mv_strtok(char* str, const char* delim)
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
		mv_vector_push_back(token_vector, temp);
		if(ip[ole] == '\0')
			break;
	}
	return(token_vector);
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

	    p_mv_vector_t token_vector = mv_strtok(input, " ");

	  	int le = 0;
	  	for(le = 0; le < mv_vector_size(token_vector); le++)
	  	{
	  		printf("Vector Data : { %s }\n", (char*)mv_vector_data_at(token_vector, le));
	  	}

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

