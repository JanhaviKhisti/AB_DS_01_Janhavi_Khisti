
#pragma once

// Headers
#include <iostream>

#ifndef SUCCESS 
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE 1
#endif

// Class Node
template<typename Node_T>
class Node
{
private:
	Node_T m_data;
	Node* m_left;
	Node* m_right;
	Node* m_parent;

	Node() : m_data((Node_T)0), m_left(nullptr), m_right(nullptr), m_parent(nullptr)
	{
		// Code
	}

	Node(Node_T initData) : m_data(initData), m_left(nullptr), m_right(nullptr), m_parent(nullptr)
	{
		// Code
	}

	~Node()
	{
		//m_data = (Node_T)0;
		m_left = nullptr;
		m_right = nullptr;
		m_parent = nullptr; 
	}

	template<typename Tree_T>
	friend class AVL_Tree;
};


template <typename Tree_T>
class AVL_Tree
{
private:
	typedef int ret_t;

	Node<Tree_T>* m_root;
	size_t m_size;

	ret_t GenericInsert(Tree_T new_data)
	{
		// Code
		Node<Tree_T>* prunner = m_root;

		while(true)
		{
			if( prunner->m_data == new_data )
			{
				std::cerr << "Data Already Present." << std::endl;
				return(FAILURE);
			}
			else if( new_data < prunner->m_data )
			{
				if( nullptr == prunner->m_left )
				{
					prunner->m_left = new Node<Tree_T>(new_data);
					prunner->m_left->m_parent = prunner;
					break;
				}
				prunner = prunner->m_left;
			}
			else 
			{
				if( nullptr == prunner->m_right )
				{
					prunner->m_right = new Node<Tree_T>(new_data);
					prunner->m_right->m_parent = prunner;
					break;
				}

				prunner = prunner->m_right;
			}
		}

		// Here we are going to add the self balancing loop LATER.
		AVL(prunner);

		m_size++;

		return(SUCCESS);
	}

	Node<Tree_T>* Successor(Node<Tree_T>* node)
	{
		// Code
		Node<Tree_T>* prunner = node->m_right;

		while( prunner->m_left )
			prunner = prunner->m_left;

		return(prunner);
	}

	Node<Tree_T>* Predecessor(Node<Tree_T>* node)
	{
		// Code
		Node<Tree_T>* prunner = node->m_left;

		while( prunner->m_right )
			prunner = prunner->m_right;

		return(prunner);
	}

	Tree_T	GenericRemove(Tree_T e_data)
	{
		// Code
		Node<Tree_T>* prunner = m_root;
		Tree_T to_return_data = (Tree_T)0;

		while( prunner )
		{
			if( e_data == prunner->m_data )
				break;
			else if( e_data < prunner->m_data )
				prunner = prunner->m_left;
			else 
				prunner = prunner->m_right;
		}

		if( nullptr == prunner )
			return((Tree_T)0);

		//	CASE 1: Both Children are null
		if( nullptr == prunner->m_left	&&
			nullptr == prunner->m_right )
			to_return_data = prunner->m_data;

		// CASE 2: Left Child Present
		else if( nullptr != prunner->m_left )
		{
			Node<Tree_T>*	predecessor = Predecessor(prunner);

			to_return_data = prunner->m_data;
			prunner->m_data = predecessor->m_data;

			prunner = predecessor; 
		}

		// Case 3: Right Child Present 
		else if( nullptr != prunner->m_right )
		{
			Node<Tree_T>* successor = Successor(prunner);

			to_return_data = prunner->m_data;
			prunner->m_data = successor->m_data;

			prunner = successor;
		}

		if( nullptr == prunner->m_parent )
		{
			m_root = nullptr;
		}
		else if( prunner == prunner->m_parent->m_left )
		{
			if( prunner->m_right )
			{
				prunner->m_parent->m_left = prunner->m_right;
			}
			else
			{
				prunner->m_parent->m_left = prunner->m_left;
			}
		}
		else
		{
			if( prunner->m_left )
			{
				prunner->m_parent->m_right = prunner->m_left;
			}
			else
			{
				prunner->m_parent->m_right = prunner->m_right;
			}
		}

		// Check for left child or right chid
		if( prunner->m_left )
			prunner->m_left->m_parent = prunner->m_parent;
		else if( prunner->m_right )
			prunner->m_right->m_parent = prunner->m_parent;

		Node<Tree_T>* temp = prunner->m_parent;

		if( prunner )
		{
			delete(prunner);
			prunner = nullptr;
		}

		prunner = temp;

		// Here we will use the self balancing loop LATER
		if( prunner )
		{
			AVL(prunner);
		}

		m_size--;

		return(to_return_data);
	}

	void InorderRecursive(Node<Tree_T>* node)
	{
		if( node->m_left )
			InorderRecursive(node->m_left);

		std::cout << "{";
		std::cout << node->m_data << "-" << BalanceFactor(node);
		std::cout << "}->";

		if( node->m_right )
			InorderRecursive(node->m_right);
	}

	void PreorderRecursive(Node<Tree_T>* node)
	{
		std::cout << "{";
		std::cout << node->m_data << "-" << BalanceFactor(node);
		std::cout << "}->";

		if( node->m_left )
			PreorderRecursive(node->m_left);

		if( node->m_right )
			PreorderRecursive(node->m_right);
	}

	void PostorderRecursive(Node<Tree_T>* node)
	{
		if( node->m_left )
			PostorderRecursive(node->m_left);

		if( node->m_right )
			PostorderRecursive(node->m_right);

		std::cout << "{";
		std::cout << node->m_data << "-" << BalanceFactor(node);
		std::cout << "}->";

	}

	void PostorderDestroy(Node<Tree_T>* node)
	{
		if( node->m_left )
			PostorderDestroy(node->m_left);

		if( node->m_right )
			PostorderDestroy(node->m_right);
		
		std::cout << "Deleting : ";
		std::cout << node->m_data;

		if( node )
		{
			delete(node);
			Node = nullptr;
		}
	}

	void InorderIteratirve(Node<Tree_T>*	node);
	void PreorderIteratirve(Node<Tree_T>* node);
	void PostorderIteratirve(Node<Tree_T>* node);

	int Height(Node<Tree_T>* node)
	{
		// Code
		if( nullptr == node)
			return(0);
		else
		{
			int left_height = Height(node->m_left);
			int right_height = Height(node->m_right);

			if( left_height >= right_height )
				return(left_height+1);
			else
				return(right_height+1);
		}
	}

	int BalanceFactor(Node<Tree_T>* node)
	{
		// Code
		int left_height = Height(node->m_left);
		int right_height = Height(node->m_right);

		return( left_height - right_height );
	}

	Node<Tree_T>* RightRotate(Node<Tree_T>* x)
	{
		// Code
		Node<Tree_T>* y = x->m_left;

		x->m_left = y->m_right;

		if( x->m_left )
			x->m_left->m_parent = x;

		y->m_right = x;

		// 	Parent Handlers
		y->m_parent = x->m_parent;

		if( x->m_parent )
		{
			if( x == x->m_parent->m_right )
				x->m_parent->m_right = y;
			else 
				x->m_parent->m_left = y;
		}

		x->m_parent = y;
		
		return(y);
	}

	Node<Tree_T>* LeftRotate(Node<Tree_T>* x)
	{
		// Code
		Node<Tree_T>* y = x->m_right;

		x->m_right = y->m_left;

		if( x->m_right )
			x->m_right->m_parent = x;

		y->m_left = x;

		//	Parent Handlers
		y->m_parent = x->m_parent;

		if( x->m_parent )
		{
			if( x == x->m_parent->m_right )
				x->m_parent->m_right = y;
			else
				x->m_parent->m_left = y;
		}

		x->m_parent = y;

		return(y);
	}

	Node<Tree_T>* Rotate(Node<Tree_T>* node)
	{
		int balance_factor = BalanceFactor(node);

		if( balance_factor < -1 )
		{
			if( nullptr == node->m_right->m_right )
				RightRotate(node->m_right);

			return(LeftRotate(node));
		}
		else if( 1 < balance_factor )
		{
			if( nullptr == node->m_left->m_left )
				LeftRotate(node->m_left);

			return(RightRotate(node));
		}

		return(node);
	}

	void AVL(Node<Tree_T>* node)
	{
		//	Code
		Node<Tree_T>* prunner = node;
		while( true )
		{
			prunner = Rotate(prunner);
			if( nullptr == prunner->m_parent )
				break;

			prunner = prunner->m_parent;
		}
		m_root = prunner;
	}

public:
	//	Default Constructor
	AVL_Tree() : m_root(nullptr), m_size(0)
	{
		// Code
	}

	// 	Destructor
	~AVL_Tree()
	{
		if( m_root )
		{
			PostorderDestroy(m_root);
			m_root = nullptr;
		}

		m_size = 0;
	}

	ret_t Insert(Tree_T new_data)
	{
		if( nullptr == m_root )
		{
			m_root = new Node<Tree_T>(new_data);
		}
		else
		{
			return( GenericInsert(new_data) );
		}

		return(SUCCESS);
	}

	Tree_T Remove( Tree_T e_data )
	{
		if( nullptr == m_root )
		{
			std::cerr << "ERROR: Tree not found" << std::endl;
			return((Tree_T)0);
		}
		else
		{
			return( GenericRemove(e_data) );
		}
	}

	void Inorder()
	{
		// Code
		if( nullptr == m_root )
		{
			std::cerr << "ERROR: Tree not found" << std::endl;
			return;
		}

		std::cout << std::endl;
		std::cout << "Inorder Recursive Traversal: " << std::endl;
		std::cout << "{START}->";
		InorderRecursive(m_root);
		std::cout << "{END}";
	}

	void Preorder()
	{
		// Code
		if( nullptr == m_root )
		{
			std::cerr << "ERROR: Tree not found" << std::endl;
			return;
		}

		std::cout << std::endl;
		std::cout << "Preorder Recursive Traversal: " << std::endl;
		std::cout << "{START}->";
		PreorderRecursive(m_root);
		std::cout << "{END}";
	}

	void Postorder()
	{
		// Code
		if( nullptr == m_root )
		{
			std::cerr << "ERROR: Tree not found" << std::endl;
			return;
		}

		std::cout << std::endl;
		std::cout << "Postorder Recursive Traversal: " << std::endl;
		std::cout << "{START}->";
		PostorderRecursive(m_root);
		std::cout << "{END}";
	}
	
};


