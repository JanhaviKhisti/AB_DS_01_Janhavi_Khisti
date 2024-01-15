
/*
	Total lines of code = 
*/

// Headers 

#include  <stdio.h>
#include  <stdlib.h>
#include  <assert.h>

#include  "mv_vector.h"

p_mv_vector_t  pvector = NULL;

extern void print_data(p_mv_vector_t  pvector)
{
	// Code
	fprintf(stdout, "\n{START}-");
	for( long le = 0; le < mv_vector_size(pvector); ++le)
	{
		fprintf(stdout, "{%lld}-", (long long)mv_vector_data_at(pvector, le));
	}
	fprintf(stdout, "{END}\n");
} 	

int main(void)
{
	// Code
	pvector = create_vector();

	mv_vector_push_back(pvector, (data_t)10);
	mv_vector_push_back(pvector, (data_t)20);
	mv_vector_push_back(pvector, (data_t)30);
	mv_vector_push_back(pvector, (data_t)40);
	mv_vector_push_back(pvector, (data_t)50);

	print_data(pvector);
	printf("pvector size = %zu\n", mv_vector_size(pvector));
	printf("pvector Capacity = %zu\n", mv_vector_capacity(pvector));

	mv_vector_push_back(pvector, (data_t)60);
	mv_vector_push_back(pvector, (data_t)70);
	mv_vector_push_back(pvector, (data_t)80);
	mv_vector_push_back(pvector, (data_t)90);
	mv_vector_push_back(pvector, (data_t)100);

	print_data(pvector);
	printf("pvector size = %zu\n", mv_vector_size(pvector));
	printf("pvector Capacity = %zu\n", mv_vector_capacity(pvector));

	mv_vector_pop_back(pvector);
	mv_vector_pop_back(pvector);
	mv_vector_pop_back(pvector);

	print_data(pvector);
	printf("pvector size = %zu\n", mv_vector_size(pvector));
	printf("pvector Capacity = %zu\n", mv_vector_capacity(pvector));

	mv_vector_destroy(&pvector);

	exit(0);

}

