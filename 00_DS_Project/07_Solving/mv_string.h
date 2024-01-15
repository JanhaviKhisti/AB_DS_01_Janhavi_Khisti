
#ifndef _MV_STRING_H
#define _MV_STRING_H

#include "mv_vector.h"

#define SUCCESS  0
#define FAILURE  1

typedef int ret_t;
typedef int len_t;
typedef int type_t;
typedef void* data_t;

// function declaration
extern len_t mv_strlen(char* str);
extern ret_t mv_strconcate(char* str1, char* str2);
extern ret_t mv_strcmp(char* str1, char* str2);
extern ret_t mv_strcmp2(char* str1, char* str2);
extern char* mv_strcpy(char* dest, char* src);
extern char* mv_strrev(char* str);

extern p_mv_vector_t mv_strtok(char* str, char* delim);

#endif   /* _MV_STRING_H */

