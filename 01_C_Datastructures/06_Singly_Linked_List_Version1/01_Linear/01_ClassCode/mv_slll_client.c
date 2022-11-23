/**
 * @file    mv_slll_client.c
 * @author  MarshallingVoid (marshallingvoid@gmail.com)
 * @brief   This file contains follows
 *          1) List Interface function calls
 *          2) List Helper function calls
 * @date    04/11/2022
 * @version 1.0
 * 
 * @copyright   Copyrights (c) 2022
 * 
 */

//	Headers
#include	<stdio.h>
#include	<stdlib.h>
#include	<assert.h>

#include	"mv_slll.h"

p_mv_sll_t plist = NULL;

print_long_data(data_t data)
{
	// Code
	fprintf(stdout, "{%lld}->", (long long)data);
}

int main(void)
{
	// Code

	plist = create_singly_list();

	for(long le = 0; le < 10; ++le)
		mv_sll_insert_back(plist, (data_t)(long long)((le+1) * 12));

	fprintf(stdout, "After List insert back:\n");

	mv_sll_print_forward(plist, print_long_data);

	for(long le = 0; le < 10; ++le)
		mv_sll_insert_front(plist, (data_t)(long long)((le+1) * 27));

	fprintf(stdout, "After List insert front:\n");

	mv_sll_print_forward(plist, print_long_data);

	mv_sll_destroy(&plist, print_long_data);

	exit(SUCCESS);
}



