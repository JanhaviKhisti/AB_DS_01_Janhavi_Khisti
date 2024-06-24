
/**
 * @File: mv_string.c
 * @Brief: This contains definitions of functions declared in header file mv_string.h
 * @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 * @Date: 20-06-2024
 */

// Headers
#include <stdio.h>
#include <stdlib.h>

#include "mv_string.h"

// String Function Definitions

// String Length
/**
 * Function Name: mv_strlen
 * Function Brief: This function gives length of string
 * Input Params: string
 * Returns: Length of string
 */
extern len_t mv_strlen(char* str)
{
	// Code
	int le = 0;

	for( le = 0; str[le] != '\0'; le++ );
	return(le);
}

// String Concate
/**
 * Function Name: mv_strconcate
 * Function Brief: This function concates two given strings
 * Input Params: 1) string1
 *				 2) string2	
 * Returns: Status
 *			SUCCESS if successful / FAILURE if unsuccessful
 */
extern ret_t mv_strconcate(char* str1, char* str2)
{
	// Code
	int size1 = mv_strlen(str1);

	for(int le = 0; le < mv_strlen(str2); le++)
	{
		str1[size1] = str2[le];
		size1++;
	}

	str1[size1] = '\0';

	return(SUCCESS);
}

// String Compare
/**
 * Function Name: mv_strcmp
 * Function Brief: This function compares two given strings
 * Input Params: 1) string1
 *				 2) string2
 * Returns: Status 
 * 			SUCCESS if successful / FAILURE if unsuccessful
 */
extern ret_t mv_strcmp(char* str1, char* str2)
{
	// Code
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

/**
 * Function Name: mv_strcmp2
 * Function Brief: This function compares two given strings
 * Input Params: 1) string1
 *				 2) string2
 * Returns: Status 
 * 			SUCCESS if successful / FAILURE if unsuccessful
 */
extern ret_t mv_strcmp2(char* str1, char* str2)
{
	// Code
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

// String Copy
/**
 * Function Name: mv_strcpy
 * Function Brief: This function copys the given strings
 * Input Params: 1) string1 dest
 *				 2) string2 src
 * Returns: copied string
 */
extern char* mv_strcpy(char* dest, char* src)
{
	// Code
	int index = 0;
	for(index = 0; src[index] != '\0'; index++)
	{
		dest[index] = src[index];
	}

	dest[index] = '\0';

	return(dest);
}

// String Reverse
/**
 * Function Name: mv_strrev
 * Function Brief: This function reverses the given string 
 * Input Params: string
 * Returns: reversed string
 */
extern char* mv_strrev(char* str)
{
	// Code
	int length;
	int len = 0;

	char* new_str = str;
	length = mv_strlen(new_str)-1;
	len = length+1;

	for(int le = 0; le < len/2; le++)
	{
		char temp;
		temp = new_str[le];
		new_str[le] = new_str[length];
		new_str[length--]= temp;

	}

	new_str[len] = '\0';

	return(new_str);
}


// String Tokanization
/**
 * Function Name: mv_strtok
 * Function Brief: This function tokenized the given string
 * Input Params: 1) string
 *				 2) delim (delimiter)
 * Returns: Pointer to token vector
 */
extern p_mv_vector_t mv_strtok(char* str, char* delim)
{
	// Code
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


