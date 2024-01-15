
#include <stdio.h>
#include <stdlib.h>

#include "mv_string.h"

// function definition
// string length
extern len_t mv_strlen(char* str)
{
	// Code
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
extern ret_t mv_strcmp(char* str1, char* str2)
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

extern ret_t mv_strcmp2(char* str1, char* str2)
{
	if( mv_strlen(str1) == mv_strlen(str2) )
	{
		for(int le = 0; le < mv_strlen(str1); le++)
		{
			if(str1[le] != str2[le])
				return(0);
		}

		return(1);
	}

	return(0);
}

// string copy
extern char* mv_strcpy(char* dest, char* src)
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


extern char* mv_strrev(char* str)
{
	// code
	int length;
	char temp;

	char* new_str = str;
	length = mv_strlen(new_str) -1;

	for(int le = 0; le < mv_strlen(new_str)/2; le++)
	{
		temp = new_str[le];
		new_str[le] = new_str[length];
		new_str[length--]= temp;

	}

	return(new_str);
}


// string tokanization
extern p_mv_vector_t mv_strtok(char* str, char* delim)
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

