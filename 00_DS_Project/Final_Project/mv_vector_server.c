
/**
 * @File: mv_vector_server.c
 * @Brief: This contains definitions of functions declared in header file mv_vector.h
 * @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 * @Date: 20-06-2024
 */

// Headers
#include	<stdio.h>
#include	<stdlib.h>
#include	<assert.h>

#include 	"mv_vector.h"

// Function declaration
void error_checking( const int 	 assert_condition,
					 const char* assert_condition_str,
					 const char* file_name,
					 const int 	 line_no,
					 const int   error_condition,
					 const char* error_str);

// Macros
#define 	ERROR_CHECKING(	assert_condition, error_condition, error_str)	{											\
																				error_checking( assert_condition,		\
																								#assert_condition, 		\
																								__FILE__,				\
																								__LINE__,				\
																								error_condition,		\
																								error_str);				\
																			}	

// Vector Helper Functions 		

/**
 * Function Name: Xmalloc
 * Function Brief: This function will allocate a memory of 'nr_of_bytes' size
 * Input Params: nr_of_bytes
 * Returns: The pointer to the memory dynamically allocated 
 */																
static void* Xmalloc(size_t nr_of_bytes)
{
	// Code
	void*  p = malloc(nr_of_bytes);

	ERROR_CHECKING( 1, NULL == p, "ERROR : Out Of Memory.\n" );

	return(p);
} 

/**
 * Function Name: Xcalloc
 * Function Brief: This function will allocate a memory of 'nr_of_bytes' size for 'nr_of_elements'
 * Input Params: 1) nr_of_elements
 *				 2) nr_of_bytes
 * Returns: The pointer to the memory dynamically allocated
 */
static void* Xcalloc(size_t nr_of_elements, size_t nr_of_bytes)
{
	// Code
	void*  p = calloc(nr_of_elements, nr_of_bytes);

	ERROR_CHECKING( 1, NULL == p, "ERROR : Out Of Memory.\n" );

	return(p); 
}

/**
 * Function Name: Xrealloc
 * Function Brief: This function will reallocate a memory 
 * Input Params: nr_of_bytes
 * Returns: the pointer to the reallocated memory
 */
static void* Xrealloc(void* p, size_t nr_of_bytes)
{
	// Code
	void* rp = realloc(p, nr_of_bytes);

	//ERROR_CHECKING( 1, NULL == p, "ERROR : Out Of Memory.\n" );

	return(rp);
}

/**
 * Function Name: error_checking
 * Function Brief: This function will check error and either print erroe message of will do assertion
 * Input Params: 1) Assert Condition
 *               2) String of Assert condition
 *               3) File where assertion occured
 *               4) Line no where assertion occured
 *               5) Error Condition
 *               6) Error Message
 * Returns: void
 */
void  error_checking( const int   assert_condition,
					  const char* assert_condition_str,
					  const char* file_name,
					  const int   line_no,
					  const int   error_condition,
					  const char* error_str)
{
	// Code
	#ifdef DEBUG
		// Check Assertion
		if( !assert_condition )
		{
			fprintf(stderr, "Assertion failed : %s, File %s, Line No %d\n", assert_condition_str, file_name, line_no);
		}
	#else	
		// Error Checking
		if( error_condition )
		{
			if( NULL != error_str )
			{
				fprintf(stderr, error_str);
				exit(FAILURE);
			}
		}
	#endif
}		


// Vector Interface Functions	

/**
 * Function Name: create_vector
 * Function Brief: This function creates vector and returns pointer to it
 * Input Params: void
 * Returns: Pointer to vector
 */
extern p_mv_vector_t  create_vector(void)
{
	// Code
	p_mv_vector_t  pvec = (p_mv_vector_t)Xmalloc(SIZE_MV_VECTOR);

	ERROR_CHECKING( NULL != pvec,
					1,
					NULL);

	pvec->capacity = 2;
	pvec->nr_of_elements = 0;
	pvec->array = (p_data_t)Xcalloc(pvec->capacity, SIZE_DATA);

	ERROR_CHECKING( NULL != pvec->array,
					1,
					NULL);

	return(pvec);
}

/**
 * Function Name: mv_vector_push_back
 * Function Brief: This function pushes data into the vector
 * Input Params: 1) vector
 *				 2) data
 * Returns: Status
 *			SUCCESS if successful / FAILURE if unsuccessful
 */
extern ret_t mv_vector_push_back(p_mv_vector_t  pvector, data_t data)
{
	// Code
	ERROR_CHECKING( NULL != pvector,
					NULL == pvector,
					"ERROR : Vector Not Found.\n");

	// Check for vectors capacity
	if( pvector->nr_of_elements == pvector->capacity )
	{
		// Double the capacity
		pvector->capacity *= 2;

		pvector->array = (p_data_t)Xrealloc(pvector->array, pvector->capacity * SIZE_DATA);
		ERROR_CHECKING( NULL != pvector->array,
						1,
						NULL);
	}

	pvector->array[ pvector->nr_of_elements ] = data;
	pvector->nr_of_elements++;

	return(SUCCESS);
}	

/**
 * Function Name: mv_vector_pop_back
 * Function Brief: This function pops dada from vector
 * Input Params: vector
 * Returns: The popped data from vector
 */
extern data_t mv_vector_pop_back(p_mv_vector_t  pvector)
{
	// Code
	ERROR_CHECKING( NULL != pvector,
					NULL == pvector ||
					0 == pvector->nr_of_elements,
					"ERROR : Vector Not Found.\n");

	// Remove the data
	pvector->nr_of_elements--;
	data_t to_return_data = pvector->array[ pvector->nr_of_elements ];

	// Reduce the capacity
	if( pvector->nr_of_elements == pvector->capacity / 2 )
	{
		pvector->capacity /= 2;
		pvector->array = (p_data_t)Xrealloc(pvector->array, pvector->capacity * SIZE_DATA);
		ERROR_CHECKING( NULL != pvector->array,
						1,
						NULL);
	}

	return(to_return_data);
}							

/**
 * Function Name: mv_vector_data_at
 * Function Brief: This function gives data at given index in vector
 * Input Params: 1) vector
 *				 2) index
 * Returns: The data at given index
 */
extern data_t  mv_vector_data_at(p_mv_vector_t  pvector, size_t index)
{
	// Code
	ERROR_CHECKING( NULL != pvector,
					NULL == pvector ||
					0 == pvector->nr_of_elements,
					"ERROR : Vector Not Found.\n");

	ERROR_CHECKING( 1,
					index >= pvector->nr_of_elements,
					"ERROR : Index out of bound.\n");

	return(pvector->array[ index ]);
}								

/**
 * Function Name: mv_vector_size
 * Function Brief: This function gives size of vector
 * Input Params: vector
 * Returns: The size of vector
 */
extern size_t  mv_vector_size(p_mv_vector_t  pvector)
{
	// Code
	ERROR_CHECKING( NULL != pvector,
					NULL == pvector,
					"ERROR : Vector Not Found.\n");

	return(pvector->nr_of_elements);
}

/**
 * Function Name: mv_vector_capacity
 * Function Brief: This function gives capacity of vector
 * Input Params: vector
 * Returns: The capacity of vector
 */
extern size_t  mv_vector_capacity(p_mv_vector_t  pvector)
{
	// Code
	ERROR_CHECKING( NULL != pvector,
					NULL == pvector,
					"ERROR : Vector Not Found.\n");

	return(pvector->capacity);
}

/**
 * Function Name: mv_vector_destroy 
 * Function Brief: This function distroys vector and free its memory
 * Input Params: Pointer to pointer of vector
 * Returns: Status 
 *			SUCCESS if successful / FAILURE if unsuccessful
 */
extern ret_t  mv_vector_destroy(pp_mv_vector_t  ppvector)
{
	// Code
	ERROR_CHECKING( NULL != ppvector,
					NULL == ppvector,
					"ERROR : Vector Not Found.\n");

	p_mv_vector_t pvector = *ppvector;

	ERROR_CHECKING( NULL != pvector,
					NULL == pvector,
					"ERROR : Vector Not Found.\n");

	if( pvector->array )
	{
		free(pvector->array);
		pvector->array = NULL;
		pvector->nr_of_elements = 0;
		pvector->capacity = 0;
	}

	if( pvector )
	{
		free(pvector);
		pvector = NULL;
	}

	*ppvector = NULL;

	return(SUCCESS);
}


