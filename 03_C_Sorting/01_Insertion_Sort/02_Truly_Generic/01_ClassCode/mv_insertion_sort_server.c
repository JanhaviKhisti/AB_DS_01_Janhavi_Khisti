

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

//	Insertion Sort Helper Function
static void assign_value( char* dest, char* src, size_t no_of_bytes )
{
	// Code
	for( size_t le = 0; le < no_of_bytes; ++le )
	{
		dest[le] = src[le];
	}
}

//	Insertion Sort Interface Function
extern ret_t mv_insertion_sort(	data_t* array, 
								long long array_size, 
								size_t element_size,
								COMPAREDATAPROC pcompareproc)
{
	// Code
	for( long long ole = 1; ole < array_size; ++ole)
	{
		//	Store the key element

		//	Limitation 1: Type of context is fixed to 8 bytes
		//	Limitation 2: Allocation of key is of only 8 bytes
		
		//	Assignment to key from array index
		//data_t key = array[ole];
		
		//	Allocate an object with the size of an element
		void* key = malloc(element_size);

		void* source_addres_from_array = (((char*)array) + ole * element_size);
		assign_value( key, source_addres_from_array, element_size);

		long long ile = ole-1;	
		
		//while( ile >= 0 && array[ile] > key )
		while( ile >= 0 && SUCCESS == pcompareproc((((char*)array) + ile * element_size), key) )
		{
			// Move the bigger from key element to next index
			
			void* dest = (((char*)array) + (ile+1) * element_size);
			void* src = (((char*)array) + ile * element_size);
			//array[ile+1] = array[ile]; 

			assign_value( dest, src, element_size );

			ile--;
		}

		// Restore the key element in the proper index place
		//array[ile+1] = key;
		assign_value( (((char*)array) + (ile+1) * element_size), key, element_size );

		if( key )
		{
			free(key);
			key = NULL;
		}
		
	}
	return(SUCCESS);

}



