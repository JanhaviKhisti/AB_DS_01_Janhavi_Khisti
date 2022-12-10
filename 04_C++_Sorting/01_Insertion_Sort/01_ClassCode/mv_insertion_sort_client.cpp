
#include	<iostream>
#include	<ctime>

#include	"mv_insertion_sort.hpp"
#include	"mv_array.hpp"

int main(void)
{
	// Code

	srand(time(0));

	long no_of_elements = 10;

	MVArray<long, 10> array;
	
	for( long le = 0; le < no_of_elements; ++le )
	{
		array[le] = rand() % 100;
	}

	std::cout<< "Before Insertion Sort" << std::endl;
	std::cout<< "START, ";
	for( long le = 0; le < no_of_elements; ++le )
	{
		std::cout << array[le] << ", ";
	}
	std::cout<< "END" << std::endl << std::endl;


	std::cout<< "Before Insertion Sort using Iterator" << std::endl;
	std::cout<< "START, ";
	for( auto itr = array.begin(); itr != array.end(); ++itr )
	{
		std::cout << *itr << ", ";
	}
	std::cout<< "END" << std::endl << std::endl;

	// Insertion Sort With Iterator Genericness
	InsertionSort(array.begin(), array.end());
	
	std::cout<< "After Insertion Sort using Iterator" << std::endl;
	std::cout<< "START, ";
	for( auto itr = array.begin(); itr != array.end(); ++itr )
	{
		std::cout << *itr << ", ";
	}
	std::cout<< "END" << std::endl << std::endl;

	// Insertion Sort With Iterator Genericness and Lambda Expression
	InsertionSort(array.begin() + 5, array.end(), [](long a, long b)
	{
		return( a > b );
	});
	
	std::cout<< "After Insertion Sort using Iterator and Lambda Expression" << std::endl;
	std::cout<< "START, ";
	for( auto itr = array.begin(); itr != array.end(); ++itr )
	{
		std::cout << *itr << ", ";
	}
	std::cout<< "END" << std::endl << std::endl;

	
	/*
	long no_of_elements = 1 + rand() % 500;

	long* array = new long[no_of_elements];

	for( long le = 0; le < no_of_elements; ++le )
	{
		array[le] = rand() % LONG_MAX;
	}

	std::cout<< "Before Insertion Sort" << std::endl;
	std::cout<< "START, ";
	for( long le = 0; le < no_of_elements; ++le )
	{
		std::cout << array[le] << ", ";
	}
	std::cout<< "END" << std::endl << std::endl;

	InsertionSort<long>(array, no_of_elements);

	std::cout<< "After Insertion Sort" << std::endl;
	std::cout<< "START, ";
	for( long le = 0; le < no_of_elements; ++le )
	{
		std::cout << array[le] << ", ";
	}
	std::cout<< "END" << std::endl << std::endl;

	delete [] array;*/

	return(0);
}
