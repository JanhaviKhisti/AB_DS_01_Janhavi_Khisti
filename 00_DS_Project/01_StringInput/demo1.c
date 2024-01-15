
#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE SIZE

char* str[MAX_VALUE];

int main(void)
{
	// Code
	// char* fgets(char *str, int n, FILE *stream)
	//fgets(str, SIZE, stdin);

	fgets(str, SIZE, stdin);
	printf(" String is : %s", str);

	while(1)
	{ 
		if(str == "exit\n" || str == "quit\n")
			break;
	}

	exit(EXIT_SUCCESS);
}
