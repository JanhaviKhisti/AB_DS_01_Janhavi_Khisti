
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mv_quick_sort.h"

ret_t  compare(data_t data1, data_t data2)
{
	return(data1 < data2);

	return(FALSE);
}

int main(void)
{
	// Code
	srand(time(0));

	long long no_of_elements = 10;

	long  long* array = (long long*)calloc(no_of_elements, sizeof(long long));

	for(long le = 0; le < no_of_elements; le++)
		array[le] = le + rand() % 20;

	printf("Array Before QuickSort: \n{Start}-");
	for(long long le = 0; le < no_of_elements; le++)
		printf("{%lld}-", (long long)array[le]);
	printf("{End}\n\n");

	QuickSort((data_t*) array, 0, no_of_elements-1, compare);

	printf("Array After QuickSort: \n{Start}-");
	for(long long le = 0; le < no_of_elements; le++)
		printf("{%lld}-", (long long)array[le]);
	printf("{END}\n\n");

	exit(0);
}

