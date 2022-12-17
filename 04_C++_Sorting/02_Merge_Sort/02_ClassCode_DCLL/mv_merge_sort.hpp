
#pragma	once

template<typename T_SORT, class Compare>
static void Merge(T_SORT& array, long long first, long long mid, long long last, Compare compare)
{
	// Code

	//	Calculate left sub array size
	long long left_size = mid - first + 1;

	//	Calculate right sub array size
	long long right_size = last - (mid+1) + 1;

	//	Allocate left and right sub array;
	T_SORT	left = T_SORT(array, first, mid);
	T_SORT	right = T_SORT(array, mid+1, last);

	long long left_index = 0;
	long long right_index = 0;
	long long array_index = first;

	//	Merge the two sub array by following the sorting condition
	while( left_index != left_size && right_index != right_size )
	{
		if( compare(left[left_index], right[right_index]) )
		{
			//std::cout << "--1 " << std::endl;
			array[ array_index ] = left[left_index];
			left_index++;
		}
		else
		{
			//std::cout << "--2 " << std::endl;
			array[array_index] = right[right_index];
			right_index++;
		}
		array_index++;
	}

	//	Case 1 if left is complete and right remains
	while( 	left_index == left_size &&
			right_index != right_size )
	{
		//std::cout << "--3 " << std::endl;
		array[array_index] = right[right_index];
		right_index++;
		array_index++;
	}

	//	Case 2 if left remains and right is complete
	while( 	left_index != left_size &&
			right_index == right_size )
	{
		//std::cout << "--4 " << std::endl;
		array[array_index] = left[left_index];
		left_index++;
		array_index++;
	}

	/*delete [] right;
	delete [] left;*/
}

template<typename T_SORT, class Compare>
static void Partition(T_SORT& array, long long first, long long last, Compare compare)
{
	//	Code
	if( first < last )
	{
		long long mid = (last - first) / 2 + first;	//	(first + last) / 2;

		Partition(array, first, mid, compare);
		
		Partition(array, mid+1, last, compare);
		Merge(array, first, mid, last, compare);
	}
}

/*
 * 
 * 	Function:	Merge Sort
 * 
 * 	Identifier	:	MergeSort
 * 	Input:	1) Array
 * 			2) Size
 * 
 * 	Output:	None
 */
template<typename T_SORT, class Compare>
extern	void MergeSort(T_SORT& array, long long size, Compare compare)
{
	//	Code

	Partition(array, 0, size-1, compare);	
}



