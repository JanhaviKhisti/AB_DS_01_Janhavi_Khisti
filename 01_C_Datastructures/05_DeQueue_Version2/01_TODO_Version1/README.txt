
Directory : 
			D:\AB_DS Batch 1\Git_Codes\AB_DS_Janhavi_Khisti\01_C_Datastructures\05_DeQueue_Version2\01_TODO_Version1
			
Files :
		1) mv_dequeue.h
		2) mv_dequeue_server.c
		3) mv_dequeue_client.c
		4) mv_vector.h
		5) mv_vector.c

Description :

1) mv_dequeue.h  : 
						This header files contains all the declaration of interface functions
			 			 of 'mv_queue'

2) mv_dequeue_server.c : 
	|					This Source file contains all the function definitions declared in mv_dequeue.h
	|
	|
	|_>	Updation :
					1) New function is added 
						  i.e check_deque_conditions that takes pointer to deque and ERROR CODES
						  check_deque_conditions function is specifically designed to make error handling code more redundant
						  by simply providing ERROR CODES

					2) DeQueue here is implemented using vector, on server 
						side queue is using vector to enque, deque, print and destory 
						data in queue.

						so now it behaves as a server for client but as a client
						for mv_vector_server.c

3) mv_dequeue_client.c : 
						This source file contains interface function calls made 
						by client in order to manage generic data on queueue data structure and 
						therefore needs callback function as client is the only who
	  					knows how to represent data on console and in memory
    
4) mv_vector.h  : 
				 This header files contains all the declaration of interface functions of 'mv_vector'

5) mv_vector.c : 
				 This Source file contains all the function definitions declared in mv_vector_header.h

