/*
	Total lines of code = (header-> base_iterator) 43 + (header-> queue) 353
						  + (queue client) 57 = 453
*/


// Headers

#include	<iostream>

#include	"mv_queue.hpp"

MVQueue<long>* pqueue;

int main(void)
{
	// Code
	pqueue = new MVQueue<long>(10);

	pqueue->PushBack(10);
	pqueue->PushBack(20);
	pqueue->PushBack(30);
	pqueue->PushBack(40);
	pqueue->PushBack(50);
	pqueue->PushBack(60);
	pqueue->PushBack(70);
	pqueue->PushBack(80);
	pqueue->PushBack(90);
	pqueue->PushBack(100);

	std::cout << std::endl << std::endl;
	std::cout << "Queue After Push Back." << std::endl;
	std::cout << (*pqueue);

	std::cout << std::endl << std::endl;
	std::cout << "Popped Data = " << pqueue->PopFront() << std::endl;
	std::cout << "Popped Data = " << pqueue->PopFront() << std::endl;
	std::cout << "Popped Data = " << pqueue->PopFront() << std::endl;
	std::cout << "Popped Data = " << pqueue->PopFront() << std::endl;

	std::cout << std::endl << std::endl;
	std::cout << "Queue After Pop Front." << std::endl;
	std::cout << (*pqueue);	

	pqueue->PushBack(999);
	pqueue->PushBack(888);
	pqueue->PushBack(777);

	std::cout << std::endl << std::endl;
	std::cout << "Queue After Push Back." << std::endl;
	std::cout << (*pqueue);

	delete(pqueue);

	return(SUCCESS);
	
}	


