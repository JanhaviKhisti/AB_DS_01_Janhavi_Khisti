/*
	Total lines of code = (header-> base_iterator) 43 + (header-> vector) 420 + (header-> stack) 101
						  + (stack client) 50 =  614  
*/


//	Headers

#include <iostream>

#include "mv_stack.hpp"


MVStack<long> *pstack = NULL;

int main(void)
{
	// Code

	pstack = new MVStack<long>();

	for( long le = 0; le < 20; ++le )
	{
		pstack->Push( (le+1) * 22 );
	}

	std::cout << std::endl;

	std::cout << "After Stack Data Push" << std::endl;
	std::cout << (*pstack);

	std::cout << std::endl;

	std::cout << "Popped Data : " << pstack->Pop() << std::endl;
	std::cout << "Popped Data : " << pstack->Pop() << std::endl;
	std::cout << "Popped Data : " << pstack->Pop() << std::endl;
	std::cout << "Popped Data : " << pstack->Pop() << std::endl;
	std::cout << "Popped Data : " << pstack->Pop() << std::endl;

	std::cout << std::endl; 

	std::cout << "After Stack Data Pop" << std::endl;
	std::cout << (*pstack);

	delete (pstack);

	return (SUCCESS);

}

