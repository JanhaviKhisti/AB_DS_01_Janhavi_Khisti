
/**
 * @File: mv_string.h
 * @Brief: This contains function declarations for mv_string
 * @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 * @Date: 20-06-2024
 */

#ifndef _MV_STRING_H
#define _MV_STRING_H

// Header File
#include "mv_vector.h"

// Macros
#ifndef  	SUCCESS
#define  	SUCCESS  	0
#endif

#ifndef  	FAILURE
#define  	FAILURE  	1
#endif

// Type Definitions
typedef  int 	ret_t;
typedef  int 	len_t;
typedef  int 	type_t;
typedef  void* 	data_t;


// String Function Declarations

// String Length
/**
 * Function Name: mv_strlen
 * Function Brief: This function gives length of string
 * Input Params: string
 * Returns: Length of string
 */
extern len_t mv_strlen(char* str);

// String Concate
/**
 * Function Name: mv_strconcate
 * Function Brief: This function concates two given strings
 * Input Params: 1) string1
 *				 2) string2	
 * Returns: Status
 *			SUCCESS if successful / FAILURE if unsuccessful
 */
extern ret_t mv_strconcate(char* str1, char* str2);

// String Compare
/**
 * Function Name: mv_strcmp
 * Function Brief: This function compares two given strings
 * Input Params: 1) string1
 *				 2) string2
 * Returns: Status 
 * 			SUCCESS if successful / FAILURE if unsuccessful
 */
extern ret_t mv_strcmp(char* str1, char* str2);

/**
 * Function Name: mv_strcmp2
 * Function Brief: This function compares two given strings
 * Input Params: 1) string1
 *				 2) string2
 * Returns: Status 
 * 			SUCCESS if successful / FAILURE if unsuccessful
 */
extern ret_t mv_strcmp2(char* str1, char* str2);

// String Copy
/**
 * Function Name: mv_strcpy
 * Function Brief: This function copys the given strings
 * Input Params: 1) string1 dest
 *				 2) string2 src
 * Returns: copied string
 */
extern char* mv_strcpy(char* dest, char* src);

// String Reverse
/**
 * Function Name: mv_strrev
 * Function Brief: This function reverses the given string 
 * Input Params: string
 * Returns: reversed string
 */
extern char* mv_strrev(char* str);

// String Tokenization
/**
 * Function Name: mv_strtok
 * Function Brief: This function tokenized the given string
 * Input Params: 1) string
 *				 2) delim (delimiter)
 * Returns: Pointer to token vector
 */
extern p_mv_vector_t mv_strtok(char* str, char* delim);

#endif   /* _MV_STRING_H */

