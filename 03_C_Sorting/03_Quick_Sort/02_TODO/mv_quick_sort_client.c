
#include <stdio.h>
#include <stdlib.h>

#include "mv_quick_sort.h"
#include "mv_dcll.h"

ret_t  compare(data_t data1, data_t data2)
{
	return(data1 < data2);

	return(FALSE);
}

void showdata(data_t data)
{
	// Code
	fprintf(stdout, "{%lld}->", (long long)data);
}

int main(void)
{
	// Code
	p_mv_dcll_t plist = create_doubly_circular_list();

	for(long long le = 10; le >= 1; le--)
	{
		mv_dcll_insert_back(plist, (data_t)le);
	}

	mv_dcll_insert_back( plist, (data_t) 23);
	mv_dcll_insert_back( plist, (data_t) 25);
	mv_dcll_insert_back( plist, (data_t) 21);

	mv_dcll_print_forward(plist, showdata);

	QuickSort(plist, 0, (mv_dcll_get_size(plist) - 1), compare);

	mv_dcll_print_forward(plist, showdata);

	exit(0);
}

