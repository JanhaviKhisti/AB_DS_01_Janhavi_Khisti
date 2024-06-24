
/**
 * @File: mv_expression_solving.h
 * @Brief: This contains function declarations for mv_expression_solving
 * @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 * @Date: 21-06-2024
 */

#ifndef _MV_EXPRESSION_SOLVING_H
#define _MV_EXPRESSION_SOLVING_H

// Headers
#include "mv_vector.h"
#include "mv_stack.h"
#include "mv_dcll.h"
#include "mv_string.h"

//	Constant Literals
#ifndef	SUCCESS	
#define	SUCCESS 0
#endif

#ifndef	FAILURE
#define	FAILURE	1
#endif	

// Type Definitions
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

// Enums
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

// Struct Type Definition
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

// Interface Functions for Expression Solving

/**
 * Function Name: mv_type_checking
 * Function Brief: This function gives type of tokenized string
 * Input Params: string
 * Returns: The type of string 
 */
extern type_t mv_type_checking(char* ip);

/**
 * Function Name: create_object_vector
 * Function Brief: This function creates object vector
 * Input Params: vector 
 * Returns: vector
 */
extern p_mv_vector_t create_object_vector(p_mv_vector_t pvector);

/**
 * Function Name: get_operator_priority
 * Function Brief: This function gives priority of operators
 * Input Params: object
 * Returns: The priority of operator
 */
extern ret_t get_operator_priority(p_mv_object_t obj);

/**
 * Function Name: create_expression_stack
 * Function Brief: This function creates expression stack of given expression
 * Input Params: vector 
 * Returns: The created stack
 */
extern p_mv_stack_t create_expression_stack(p_mv_vector_t pvector);

/**
 * Function Name: create_expression_tree
 * Function Brief: This function creates expression tree of given expression
 * Input Params: stack
 * Returns: The expression node object
 */
extern p_mv_object_t create_expression_tree(p_mv_stack_t expression_stack);

/**
 * Function Name: expression_solver
 * Function Brief: This function actually solves the expression
 * Input Params: object
 * Returns: void
 */
extern void expression_solver(p_mv_object_t object);


/*******************************************************************************/

// For Operation Solving

// Type Definitions
struct mv_value_object;

typedef struct mv_value_object  mv_value_object_t;
typedef struct mv_value_object* p_mv_value_object_t;

struct mv_symbol_object;

typedef struct mv_symbol_object  mv_symbol_object_t;
typedef struct mv_symbol_object* p_mv_symbol_object_t;

// Struct Type Definitions
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

// Enums
enum 
{
	NO = 0,
	MV_TYPE_INT,	// 1
	MV_TYPE_FLOAT,	// 2
	MV_TYPE_DOUBLE	// 3
};

// Interface Functions for Operation Solving 

/**
 * Function Name: Addition
 * Function Brief: This function performs addition operation
 * Input Params: 1) object1
 *				 2) object2
 * Returns: answer string
 */
extern char* Addition(p_mv_object_t object1, p_mv_object_t object2);

/**
 * Function Name: Subtraction
 * Function Brief: This function performs subtraction operation
 * Input Params: 1) object1
 *				 2) object2
 * Returns: answer string
 */
extern char* Subtraction(p_mv_object_t object1, p_mv_object_t object2);

/**
 * Function Name: Multiplication
 * Function Brief: This function performs multiplication operation
 * Input Params: 1) object1
 *				 2) object2
 * Returns: answer string
 */
extern char* Multiplication(p_mv_object_t object1, p_mv_object_t object2);

/**
 * Function Name: Assignment
 * Function Brief: This function performs assignment operation
 * Input Params: 1) object1
 *				 2) object2
 * Returns: void
 */
extern void Assignment(p_mv_object_t object1, p_mv_object_t object2);


#endif   /* _MV_EXPRESSION_SOLVING_H */


