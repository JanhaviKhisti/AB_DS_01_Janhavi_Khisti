

#pragma	once

//	Constant Literals

#ifndef	SUCCESS
#define	SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE 1
#endif

/**
 * 
 * 
 * Algorithm: Partition
 * 
 * Partition(A, first, last)
 * {
 * 		pivot = A[last]
 * 
 * 		i = first - 1
 * 
 * 		loop( j = first to last - 1 )
 * 		{
 * 			if( A[j] <= pivot )
 * 			{
 * 				i = i+1
 * 				swap(A[i], A[j])
 * 			}
 * 		}
 * 		swap(A[i+1], A[j])
 * 		return(i+1)
 * }
 * 
 */

template<typename T, class Compare>
long long Partition(T* array, long long first, long long last, Compare compare)
{
	// Code
	T pivot = array[last];

	long long ole = first - 1;

	long long ile = 0;

	for( ile = first; ile < last; ++ile )
	{
		if( compare(array[ile], pivot) )
		{
			++ole;

			// Swap
			if( ole != ile )
			{
				T temp = array[ole];
				array[ole] = array[ile];
				array[ile] = temp;
			}
		}
	}

	// Swap
	++ole;
	T temp = array[ole];
	array[ole] = array[ile];
	array[ile] = temp;

	return(ole);
}

template<typename T, class Compare>
long long Partition(T& array, long long first, long long last, Compare compare)
{
	// Code
	auto pivot = array[last];

	long long ole = first - 1;

	long long ile = 0;

	for( ile = first; ile < last; ++ile )
	{
		if( compare(array[ile], pivot) )
		{
			++ole;

			// Swap
			if( ole != ile )
			{
				auto temp = array[ole];
				array[ole] = array[ile];
				array[ile] = temp;
			}
		}
	}

	// Swap
	++ole;
	auto temp = array[ole];
	array[ole] = array[ile];
	array[ile] = temp;

	return(ole);
}


/**
 * 
 * Algorithm: QuickSort
 * 
 * QuickSort(A, first, last)
 * {
 * 		if( first < last )
 * 		{
 * 			// Find the Mid
 * 			mid = Partition(A, first, last)
 * 
 * 			// Call to Quick Sort for LEFT SUB-ARRAY
 * 			QuickSort(A, first, mid-1)
 * 
 * 			// Call to Quick Sort for RIGHT SUB-ARRAY
 * 			QuickSort(A, mid+1, last) 
 * 		}
 * }
 * 
 */

//	Quick Sort
template<typename T, class Compare>
void	QuickSort( T* array, long long first, long long last, Compare compare)
{
	// Code
	if( first < last )
	{
		//	Find the mid
		long long mid = Partition( array, first, last, compare);

		//	Call to QuickSort for LEFT SUB-ARRAY
		QuickSort(array, first, mid-1, compare);

		//	Call to QuickSort for RIGHT SUB-ARRAY
		QuickSort(array, mid+1, last, compare);
	}
}

//	Quick Sort
template<typename T, class Compare>
void	QuickSort( T& array, long long first, long long last, Compare compare)
{
	// Code
	if( first < last )
	{
		//	Find the mid
		long long mid = Partition( array, first, last, compare);

		//	Call to QuickSort for LEFT SUB-ARRAY
		QuickSort(array, first, mid-1, compare);

		//	Call to QuickSort for RIGHT SUB-ARRAY
		QuickSort(array, mid+1, last, compare);
	}
}



