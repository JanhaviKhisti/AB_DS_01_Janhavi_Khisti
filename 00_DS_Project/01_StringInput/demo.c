
#include <stdio.h>
#include <stdlib.h>

// type definition
typedef int ret_t;
typedef int len_t;

// function declaration
len_t mv_strlen(const char* str);


// function definition
len_t mv_strlen(const char* str)
{
	int le = 0;

	for( le = 0; str[le] != '\0'; le++ );

	return(le);
}

int main()
{
 
	while(1)
	{
		// allocating memory
		char* string = malloc(2048);

		// user input
	   	fgets(string, 2048, stdin);

	   	// reallocation 
	   	string = realloc(string, mv_strlen(string));

	  	printf("\nString is : %s", string);

	  	if(string == 'exit')
	  		break;
	  	
	  	// free memory
	  	free(string);

	}
   
   exit(0);
}

