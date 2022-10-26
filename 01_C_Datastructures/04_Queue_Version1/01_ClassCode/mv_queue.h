
#ifndef		_MV_QUEUE_H
#define		_MV_QUEUE_H

//	Constant Literals

#ifndef		SUCCESS
#define		SUCCESS		0
#endif

#ifndef		FAILURE
#define		FAILURE		1
#endif

//	Type definitions

struct mv_queue;	// Struct Declaration

typedef	 struct mv_queue 	mv_queue_t;
typedef  struct mv_queue* 	p_mv_queue_t;
typedef  struct mv_queue**	pp_mv_queue_t;

typedef  void*	  data_t;
typedef  data_t*  p_data_t;

#define		SIZE_DATA	(sizeof(data_t))

typedef	 int  ret_t;

typedef	 void (*PRINTDATAPROC)  (data_t);
typedef	 void (*DELETEDATAPROC) (data_t);


//	Struct Type Definitions
struct mv_queue
{
	p_data_t	queue;	//	data array
	size_t		head;	//	head place holder
	size_t		tail;	//	tail place holder
	size_t 		length;	//	total number of elements
	size_t 		no_of_elements;
};

#define		SIZE_QUEUE		(sizeof(mv_queue_t))

//	Queue Interface Functions		( given to client to use queue )

/*
  Fuction
  	identifier	:	create_default_queue
  	input		:	void
  	output		:	pointer to queue
*/
extern	p_mv_queue_t 	create_default_queue(void);


/*
  Function
  	identifier	:	create_custom_queue
  	input		:	number of elements
  	output		:	pointer to queue
*/
extern	p_mv_queue_t  create_custom_queue(size_t nr_of_elements);

/*
 Function
  	identifier	:	mv_queue_enqueue
  	input		:	1) queue
  					2) data
  	output		:	status(success or failure)
*/
extern	ret_t 	mv_queue_enqueue(p_mv_queue_t pqueue, data_t data);


/*
  Function 
  	identifier	:	mv_queue_dequeue
  	input		:	queue
  	output		:	returning popped data
*/
extern	data_t 	mv_queue_dequeue(p_mv_queue_t pqueue);


/*
  Function
  	identifier	:	mv_queue_print_data
  	input		:	1) queue
  					2) pointer to function 
  	output		:	status(success or failure)
*/
extern	ret_t 	mv_queue_print_data(p_mv_queue_t pqueue, PRINTDATAPROC pprintfunc );


/*
  Function
  	identifier	:	mv_queue_length
  	input		:	queue
  	output		:	returning size of queue
*/
extern	size_t 	mv_queue_length(p_mv_queue_t pqueue);


/*
  Function
  	identifier	:	mv_queue_destroy
  	input		:	1) double pointer to queue
  	output		:	pointer to function
*/
extern	ret_t	mv_queue_destroy( pp_mv_queue_t, DELETEDATAPROC pdeletefunc );

#endif		/* _MV_QUEUE_H */

