
#include <stdio.h>
#include <stdlib.h>

#include "mv_quick_sort.h"
#include "mv_dcll.h"

static long long Partition(p_mv_dcll_t list, long long first, long long last, COMPARE compare)
{
	data_t pivot = mv_dcll_get_data_at(list, last);

	long long i = first - 1;

	long long j = 0;

	for(j = first; j < last; j++)
	{
		if(compare(mv_dcll_get_data_at(list, j),pivot))
		{
			i++;

			// swap
			if(i != j)
			{
				data_t temp = mv_dcll_get_data_at(list, i);
				mv_dcll_add_data_at(list, mv_dcll_get_data_at(list, j), i);
				mv_dcll_add_data_at(list, temp, j);
			} 
		}
	}

	// swap
	i++;
	data_t temp = mv_dcll_get_data_at(list, i);
	mv_dcll_add_data_at(list, mv_dcll_get_data_at(list, j), i);
	mv_dcll_add_data_at(list, temp, j);

	return(i);
}

extern void  	QuickSort(p_mv_dcll_t list, long long first, long long last, COMPARE compare)
{
	if(first < last)
	{
		long long mid = Partition(list, first, last, compare);

		// Call to QuickSort for LEFT SUB-ARRAY
		QuickSort(list, first, mid-1, compare);

		// Call to QuickSort for Right SUB_ARRAY
		QuickSort(list, mid+1, last, compare);
	}
}

