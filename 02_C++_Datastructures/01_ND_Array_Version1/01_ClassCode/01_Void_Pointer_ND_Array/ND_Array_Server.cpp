
// Headers
#include  <iostream>
#include  <cstdarg>

#include  "ND_Array.hpp"

// Class Function Defination

// Parameterized Constructor
MVArray::MVArray(size_t no_of_dimensions, ...)
{
	// Code
	if( 0 == no_of_dimensions )
	{
		std::cerr << "ERROR : Number of Dimension cannot be 0 or less than 0."<< std::endl;
		return;
	}

	// Set no of dimensions
	this->no_of_dimensions = no_of_dimensions;

	// Allocate array to store each dimension
	this->dimension_array = new size_t[ no_of_dimensions ];

	va_list args;

	va_start(args, no_of_dimensions);

	for( long le = 0; le < no_of_dimensions; ++le )
	{
		this->dimension_array[le] = va_arg(args, long);
	}

	va_end(args);

	// Find Total No of Elements
	size_t  no_of_elements = dimension_array[0];

	for( long le = 1; le < no_of_dimensions; ++le)
	{
		no_of_elements *= dimension_array[le];
	}

	// Allocate Data Array
	this->data_array = new data_t[ no_of_elements ];

	// Allocate To Jump Array
	this->to_jump_dimension_array = new size_t[ no_of_dimensions ];

	this->to_jump_dimension_array[ no_of_dimensions - 1 ] = 1;

	// Set To Jump Array
	for( long le = no_of_dimensions - 2; le >= 0; --le)
	{
		this->to_jump_dimension_array[le] = this->to_jump_dimension_array[le+1] * this->dimension_array[le+1];
	}
}


// Destructor
MVArray::~MVArray()
{
	// Code

	if( this->to_jump_dimension_array )
	{
		delete [] this->to_jump_dimension_array;
	}

	if( this->data_array )
	{
		delete [] this->data_array;
	}

	if( this->dimension_array )
	{
		delete [] this->dimension_array;
	}
}


// Setter Member Functions
ret_t MVArray::SetData(data_t data, ...)
{
	// Code
	size_t* indices = new size_t[ no_of_dimensions ];

	va_list args;

	va_start(args, data);

	for( long le = 0; le < no_of_dimensions; ++le )
	{
		indices[le] = va_arg(args, long);
	}

	va_end(args);

	// Calulate the required index
	size_t required_index = 0;

	for( long le = 0; le < no_of_dimensions; ++le )
	{
		required_index = required_index + indices[le] * to_jump_dimension_array[le];
	}

	data_array[required_index] = data;

	delete [] indices;

	return(SUCCESS);
}


// Getter Member Functions
data_t MVArray::GetData(...)
{
	size_t* indices = new size_t[no_of_dimensions];

	va_list args;

	va_start(args, this);

	for( long le = 0; le < no_of_dimensions; ++le )
	{
		indices[le] = va_arg(args, long);
	}

	va_end(args);

	long required_index = 0;

	for( long le = 0; le < no_of_dimensions; ++le )
	{
		required_index = required_index + indices[le] * to_jump_dimension_array[le];
	}

	data_t  to_return_data = data_array[required_index];

	delete [] indices;

	return(to_return_data);
}


// Get size of dimension
size_t MVArray::GetDimensionSize(size_t index) const
{
	// Code
	return( this->dimension_array[index] );
} 

