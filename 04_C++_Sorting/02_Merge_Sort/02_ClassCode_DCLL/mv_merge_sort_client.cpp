
#include	<iostream>
#include	<ctime>

#include	"mv_merge_sort.hpp"

#include	"mv_array.hpp"
#include	"mv_dcll.hpp"

long long no_of_elements = 100;//1 + rand() % 100;
MVArray<long long, 2> array;

MV_DCLL<long long>	list;

int main(void)
{
	//Code

	srand(time(0));

	/*std::cout << "Sorting using Array Data Structure:" << std::endl;
	for( long long le = 0; le < no_of_elements; ++le )
	{
		array[le] = 1 + rand() % 100;//LONG_MAX;
	}

	std::cout << "Before Merge Sorting:" << std::endl;
	for( long long le = 0; le < no_of_elements; ++le )
		std::cout << array[le] << ", ";
	std::cout << std::endl << std::endl;

	MergeSort(array, array.Size(), [](long long a, long long b)
	{
		return( a < b );
	});

	std::cout << "After Merge Sorting:" << std::endl;
	for( long long le = 0; le < no_of_elements; ++le )
		std::cout << array[le] << ", ";
	std::cout << std::endl << std::endl;*/

	std::cout << "Sorting using List Data Structure:" << std::endl;
	for( long long le = 0; le < no_of_elements; ++le )
	{
		list.InsertBack(1 + rand() % 100);//LONG_MAX);
	}

	std::cout << "Before Merge Sorting List:" << std::endl << list << std::endl;

	MergeSort(list, list.Size(), [](long long a, long long b)
	{
		return(a < b);
	});

	std::cout << "After Merge Sorting List:" << std::endl << list << std::endl;

	return(0);
}

