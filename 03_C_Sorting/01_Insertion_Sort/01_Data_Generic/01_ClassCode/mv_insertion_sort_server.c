
/*
 * Algorithm:
 * 		
 * InsertionSort(A)
 * {
 * 		loop( i = 1 to A.length - 1 )
 * 		{
 * 			key = A[i]
 * 			
 * 			j = i-1
 * 			loop( j >= 0 && A[j] > key )
 * 			{
 * 				A[j+1] = A[j]
 * 			}	
 * 			A[j+1] = key
 * 		}
 * } 
 *
 */

#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_insertion_sort.h"

extern ret_t mv_insertion_sort(	data_t* array, 
								long long array_size,
								COMPAREDATAPROC pcompareproc)
{
	// Code
	for( long long ole = 1; ole < array_size; ++ole)
	{
		//	Store the key element

		//	Limitation 1: Type of context is fixed to 8 bytes
		//	Limitation 2: Allocation of key is of only 8 bytes
		
		//	Assignment to key from array index
		data_t key = array[ole];

		long long ile = ole-1;	

		//while( ile >= 0 && array[ile] > key )
		while( ile >= 0 && SUCCESS == pcompareproc(array[ile], key) )
		{
			// Move the bigger from key element to next index
			array[ile+1] = array[ile]; 

			ile--;
		}

		// Restore the key element in the proper index place
		array[ile+1] = key;
		
	}

	return(SUCCESS);
}


