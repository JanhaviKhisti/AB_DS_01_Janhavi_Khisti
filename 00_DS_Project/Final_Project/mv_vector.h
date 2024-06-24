
/**
 * @File: mv_vector.h
 * @Brief: This contains function declarations for mv_vector
 * @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 * @Date: 20-06-2024
 */

#ifndef _MV_VECTOR_H
#define _MV_VECTOR_H

// Constant Literals 

#ifndef		SUCCESS
#define 	SUCCESS		0
#endif

#ifndef 	FAILURE
#define 	FAILURE	 	1
#endif

// Type Definitions

struct mv_vector;

typedef struct mv_vector 	mv_vector_t;
typedef struct mv_vector*	p_mv_vector_t;
typedef struct mv_vector**	pp_mv_vector_t;

typedef void* 	data_t;
typedef data_t* p_data_t;

#define SIZE_DATA (sizeof(data_t))

typedef int  ret_t;

// Struct Type Defination
struct mv_vector
{
	p_data_t  array;
	size_t 	  nr_of_elements;
	size_t    capacity;
};

#define SIZE_MV_VECTOR (sizeof(mv_vector_t))


// Vector Interface Fuctions

/**
 * Function Name: create_vector
 * Function Brief: This function creates vector and returns pointer to it
 * Input Params: void
 * Returns: Pointer to vector
 */
extern p_mv_vector_t  create_vector(void);

/**
 * Function Name: mv_vector_push_back
 * Function Brief: This function pushes data into the vector
 * Input Params: 1) vector
 *				 2) data
 * Returns: Status
 *			SUCCESS if successful / FAILURE if unsuccessful
 */
extern ret_t  mv_vector_push_back(p_mv_vector_t  pvector, data_t  data);

/**
 * Function Name: mv_vector_pop_back
 * Function Brief: This function pops dada from vector
 * Input Params: vector
 * Returns: The popped data from vector
 */
extern data_t  mv_vector_pop_back(p_mv_vector_t  pvector);

/**
 * Function Name: mv_vector_data_at
 * Function Brief: This function gives data at given index in vector
 * Input Params: 1) vector
 *				 2) index
 * Returns: The data at given index
 */
extern data_t  mv_vector_data_at(p_mv_vector_t  pvector, size_t  index);

/**
 * Function Name: mv_vector_size
 * Function Brief: This function gives size of vector
 * Input Params: vector
 * Returns: The size of vector
 */
extern size_t  mv_vector_size(p_mv_vector_t  pvector);

/**
 * Function Name: mv_vector_capacity
 * Function Brief: This function gives capacity of vector
 * Input Params: vector
 * Returns: The capacity of vector
 */
extern size_t  mv_vector_capacity(p_mv_vector_t  pvector);

/**
 * Function Name: mv_vector_destroy 
 * Function Brief: This function distroys vector and free its memory
 * Input Params: Pointer to pointer of vector
 * Returns: Status 
 *			SUCCESS if successful / FAILURE if unsuccessful
 */
extern ret_t  mv_vector_destroy(pp_mv_vector_t  ppvector);

#endif	/* _MV_VECTOR_H */

/*********************************************************************************************************************/
/*
	
	capacity = 2

	when nr_elements = 2  double the capacity = 4
	when nr_elements = 4  double the capacity = 8
	when nr_elements = 8  double the capacity = 16
	
	if nr_elements == capacity
		capacity *= 2 

	when nr_elements = capacity / 2 then reduce the capacity by half

	capacity = 8
	nr_elements = 4

	capacity = capacity / 2 ==> 4

*/

