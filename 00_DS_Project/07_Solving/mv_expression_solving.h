
#ifndef _MV_EXPRESSION_SOLVING_H
#define _MV_EXPRESSION_SOLVING_H

#include "mv_vector.h"
#include "mv_stack.h"
#include "mv_dcll.h"
#include "mv_string.h"

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


// // function declaration
// extern len_t mv_strlen(char* str);
// extern ret_t mv_strconcate(char* str1, char* str2);
// extern ret_t mv_strcmp(char* str1, char* str2);
// extern ret_t mv_strcmp2(char* str1, char* str2);
// extern char* mv_strcpy(char* dest, char* src);
// extern char* mv_strrev(char* str);

// extern p_mv_vector_t mv_strtok(char* str, char* delim);

extern type_t mv_type_checking(char* ip);

extern p_mv_vector_t create_object_vector(p_mv_vector_t pvector);

extern ret_t get_operator_priority(p_mv_object_t obj);
extern p_mv_stack_t create_expression_stack(p_mv_vector_t pvector);
extern p_mv_object_t create_expression_tree(p_mv_stack_t expression_stack);
extern void expression_solver(p_mv_object_t object);

/*******************************************************************************/

struct mv_value_object;

typedef struct mv_value_object  mv_value_object_t;
typedef struct mv_value_object* p_mv_value_object_t;

struct mv_symbol_object;

typedef struct mv_symbol_object  mv_symbol_object_t;
typedef struct mv_symbol_object* p_mv_symbol_object_t;

struct mv_value_object
{
	type_t type;
	data_t data;
	int no_of_ref;
};
#define SIZE_MV_VALUE_OBJECT (sizeof(mv_value_object_t))

struct mv_symbol_object
{
	data_t data;
	p_mv_value_object_t pvalobj;
};
#define SIZE_MV_SYMBOL_OBJECT (sizeof(mv_symbol_object_t))

enum 
{
	NO = 0,
	MV_TYPE_INT,	// 1
	MV_TYPE_FLOAT,	// 2
	MV_TYPE_DOUBLE	// 3
};

// Operation Solving 

extern char* Addition(p_mv_object_t object1, p_mv_object_t object2);
extern char* Subtraction(p_mv_object_t object1, p_mv_object_t object2);
extern char* Multiplication(p_mv_object_t object1, p_mv_object_t object2);
extern char* Division(p_mv_object_t object1, p_mv_object_t object2);
extern char* Modulous(p_mv_object_t object1, p_mv_object_t object2);
extern void Assignment(p_mv_object_t object1, p_mv_object_t object2);



#endif   /* _MV_EXPRESSION_SOLVING_H */

