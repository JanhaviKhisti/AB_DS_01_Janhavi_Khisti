
#include <stdio.h>
#include <stdlib.h>

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


int main()
{
 
	while(1)
	{
		// allocating memory
		char* input = malloc(2048);
		char* str2 = "exit";

		// user input
	   	fgets(input, 2048, stdin);

	   	// reallocation 
	   	input = realloc(input, mv_strlen(input));

	   	input[mv_strlen(input) - 1] = '\0';

	  	printf("String is : %s\n", input);

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

