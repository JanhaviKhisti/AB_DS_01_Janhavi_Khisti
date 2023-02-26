
#include <stdio.h>
#include <stdlib.h>

#include "mv_quick_sort.h"

static long long Partition(data_t* array, long long first, long long last, COMPARE compare)
{
	data_t pivot = array[last];

	long long i = first - 1;

	long long j = 0;

	for(j = first; j < last; j++)
	{
		if(compare((data_t)(long long)array[j], (data_t)(long long)pivot))
		{
			++i;

			// swap
			if(i != j)
			{
				data_t temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			} 
		}
	}

	// swap
	++i;
	data_t temp = array[i];
	array[i] = array[j];
	array[j] = temp;

	return(i);
}

extern void  	QuickSort(data_t* array, long long first, long long last, COMPARE compare)
{
	if(first < last)
	{
		long long mid = Partition(array, first, last, compare);

		// Call to QuickSort for LEFT SUB-ARRAY
		QuickSort(array, first, mid-1, compare);

		// Call to QuickSort for Right SUB_ARRAY
		QuickSort(array, mid+1, last, compare);
	}
}

