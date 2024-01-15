
#ifndef _MV_TYPE_H
#define _MV_TYPE_H

#include "mv_vector.h"
#include "mv_stack.h"

#define SUCCESS  0
#define FAILURE  1

// type definition
struct mv_object;

typedef struct mv_object  mv_object_t;
typedef struct mv_object* p_mv_object_t;

struct mv_expression_node;

typedef struct mv_expression_node  	mv_expression_node_t;
typedef struct mv_expression_node* 	p_mv_expression_node_t;

typedef int ret_t;
typedef int len_t;
typedef int type_t;
typedef void* data_t;

enum
{
	MV_TYPE_NONE = 0,
	MV_TYPE_IDENTIFIER,				 // 1
	MV_TYPE_OPERATOR,				 // 2				
	MV_TYPE_OPERATOR_EQUAL,			 // 3
	MV_TYPE_OPERATOR_ADDITION,		 // 4
	MV_TYPE_OPERATOR_SUBTRACTION,	 // 5
	MV_TYPE_OPERATOR_MULTIPLICATION, // 6
	MV_TYPE_OPERATOR_DIVISION,		 // 7
	MV_TYPE_OPERATOR_MODULOUS,		 // 8
	MV_TYPE_IMMIDIATE,				 // 9
	MV_TYPE_EXPRESSION_NODE			 // 10
};

// struct type definition
struct mv_object
{
	int    object_type;
	void*  object_value;
};

#define SIZE_MV_OBJECT  (sizeof(mv_object_t))

struct mv_expression_node
{
	p_mv_object_t operator;
	p_mv_object_t left;
	p_mv_object_t right;
};

#define SIZE_MV_EXPRESSION_NODE (sizeof(mv_expression_node_t))


// function declaration
// string length
extern len_t mv_strlen(const char* str);

// string compare
extern ret_t mv_strcmp(const char* str1, const char* str2);

// string copy
extern char* mv_strcpy(char* dest, const char* src);

// string tokanization
extern p_mv_vector_t mv_strtok(char* str, const char* delim);

// Type Checking Function
extern type_t mv_type_checking(char* ip);

extern p_mv_vector_t create_object_vector(p_mv_vector_t pvector);

#endif   /* _MV_TYPE_H */

