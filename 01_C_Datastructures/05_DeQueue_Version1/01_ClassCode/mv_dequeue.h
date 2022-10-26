#ifndef _MV_DEQUEUE_H
#define _MV_DEQUEUE_H

//  Constant Literal

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE 1
#endif

//  Type definitions

struct mv_dequeue;

typedef struct  mv_dequeue    mv_dequeue_t;
typedef struct  mv_dequeue*   p_mv_dequeue_t;
typedef struct  mv_dequeue**  pp_mv_dequeue_t;

typedef void*    data_t;
typedef data_t*  p_data_t;
#define SIZE_DATA (sizeof(data_t))

typedef int ret_t;

typedef void (*PRINTDATAPROC)(data_t);
typedef void (*DELETEDATAPROC)(data_t);

typedef void *(*ERROR_HANDLER)(void *);

//  Struct Type Definition

struct mv_dequeue
{
    p_data_t dequeue; //  array
    long long head;   //  first index
    long long tail;   //  last index + 1
    size_t no_of_elements;
    size_t length;
};

#define SIZE_DEQUEUE (sizeof(mv_dequeue_t))

//  Dequeue Interface Functions

//  Data Structure Creation

/*
  Function 
  	identifier	:	create_default_dequeue
  	input		:	void
  	output		:	pointer to struct
*/
extern p_mv_dequeue_t create_default_dequeue();

/*
  Function 
  	identifier	:	create_custom_dequeue
  	input		:	number of elements
  	output		:	pointer to struct
*/
extern p_mv_dequeue_t create_custom_dequeue(size_t nr_of_elements);


//  Data Insertion

/*
  Function
  	identifier	:	mv_dequeue_enqueue_front
  	input		:	1) dequeue
  					2) data
  	output		:	status(success or failure)
*/
extern ret_t mv_dequeue_enqueue_front(p_mv_dequeue_t pdequeue, data_t data);

/*
  Function
  	identifier	:	mv_dequeue_enqueue_back
  	input		:	1) dequeue
  					2) data
  	output		:	status(success or failure)
*/
extern ret_t mv_dequeue_enqueue_back(p_mv_dequeue_t pdequeue, data_t data);


//  Data Removal

/*
  Function
  	identifier	:	mv_dequeue_dequeue_front
  	input		:	dequeue
  	output		:	returning popped data with front
*/
extern data_t mv_dequeue_dequeue_front(p_mv_dequeue_t pdequeue);

/*
  Function
  	identifier	:	mv_dequeue_dequeue_back
  	input		:	dequeue
  	output		:	returning popped data with back
*/
extern data_t mv_dequeue_dequeue_back(p_mv_dequeue_t pdequeue);


//  Queue Length

/*
  Function
  	identifier	:	mv_dequeue_size
  	input		:	dequeue
  	output		:	returning size of dequeue
*/
extern size_t mv_dequeue_size(p_mv_dequeue_t pdequeue);

//  Queue No of elements

/*
  Function
  	identifier	:	mv_dequeue_no_of_elements
  	input		:	dequeue
  	output		:	returning number of elements
*/
extern size_t mv_dequeue_no_of_elements(p_mv_dequeue_t pdequeue);

//  Data Print

/*
  Function
  	identifier	:	mv_dequeue_print_data
  	input		:	1) dequeue
  					2) pointer to function
  	output		:	status(success or failure)
*/
extern ret_t mv_dequeue_print_data(p_mv_dequeue_t pdequeue, PRINTDATAPROC pprintfunc);

//  Destroy Dequeue

/*
  Function
  	identifier	:	mv_dequeue_destroy
  	input		:	1) double pointer to dequeue
  					2) pointer to function
  	output		:	status(success or failure)
*/
extern ret_t mv_dequeue_destroy(pp_mv_dequeue_t ppdequeue, DELETEDATAPROC pdeletefunc);

#endif /* _MV_DEQUEUE_H */

