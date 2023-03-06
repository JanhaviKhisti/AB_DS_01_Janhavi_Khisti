

#include <iostream>

#include "mv_avl.hpp"

int main(int argc, char** argv, char** envp)
{
	// Code

	AVL_Tree<long long>* tree = new AVL_Tree<long long>();

	for( int le = 0; le < 100; le++)
		tree->Insert((le+1) * 6);

	tree->Inorder();
	std::cout << std::endl;
	tree->Preorder();
	std::cout << std::endl;
	tree->Postorder();
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << "Removed Data: " << tree->Remove(40);
	std::cout << std::endl;
	std::cout << std::endl;

	tree->Inorder();
	std::cout << std::endl;
	tree->Preorder();
	std::cout << std::endl;
	tree->Postorder();
	std::cout << std::endl;

	exit(EXIT_SUCCESS);

}


