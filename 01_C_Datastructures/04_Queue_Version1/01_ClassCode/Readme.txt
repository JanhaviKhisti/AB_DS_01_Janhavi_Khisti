
Directory : 
			D:\AB_DS Batch 1\Git Codes\AB_DS_Janhavi_Khisti\01_C_Datastructures\04_Queue_Version1\01_ClassCode
			
Files :
		1) mv_queue.h
		2) mv_queue_server.c
		3) mv_queue_client.c


Description :

1) mv_queue.h : 
				This header file contains all the declaration of interface functions of 
				 generic 'mv_queue'

2) mv_queue_server.c : 
		|				This source file contain all the definition of interface function of
		|				 generic 'mv_queue' 
		|
		|__> Updation :
						1) Error checking function is modified in a way that is used to handle error by accepting
						   argument as pointer to error_handler and also argument as void pointer to parameter of 
						   of error handler
							
							error_checking( assert_condition, 
											assert_condition_str,
											filename,
											line_no,
											error_condition,
											err_msg,
											void* (*perror_handler)(void*),
											void* error_handler_params )

3) mv_queue_client.c : 	
						This client file contains interface function calls made by client

