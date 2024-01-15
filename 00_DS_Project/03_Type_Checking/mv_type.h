
#ifndef _MV_TYPE_H
#define _MV_TYPE_H

#include "mv_vector.h"

#define SUCCESS  0
#define FAILURE  1

// type definition
struct mv_object;

typedef struct mv_object  mv_object_t;
typedef struct mv_object* p_mv_object_t;

typedef int ret_t;
typedef int len_t;
typedef int type_t;

// struct type definition
struct mv_object
{
	int    object_type;
	void*  object_value;
};

#define SIZE_MV_OBJECT  (sizeof(mv_object_t))


// function declaration
// string length
extern len_t mv_strlen(const char* str);

// string compare
extern ret_t mv_strcmp(const char* str1, const char* str2);

// string copy
extern char* mv_strcpy(char* dest, const char* src);

// string tokanization
extern p_mv_vector_t mv_strtok(char* str, const char* delim);


static ret_t check_immediate(char* input);
static ret_t check_identifier(char* input);
static ret_t check_operator(char* input);


static p_mv_object_t create_object(void);

// Type Checking Function
extern type_t mv_type_checking(char* ip);

extern p_mv_vector_t create_object_vector(p_mv_vector_t pvector);

#endif   /* _MV_TYPE_H */

