
// Headers
#include <stdio.h>
#include <stdlib.h>

#include "mv_bst.h"

// Constant Literals and Macros
#define ERROR_LOG(error_str) (fprintf(stderr, "ERROR : %s\n", error_str))

// Helper Functions

static void* Xmalloc(size_t no_of_bytes)
{
	// Code
	void* p = malloc(no_of_bytes);

	if(NULL == p)
	{
		ERROR_LOG("Out Of Memory");
		exit(FAILURE);
	}

	return(p);
}

static p_node_t create_node(data_t new_data)
{
	// Code
	p_node_t pnode = (p_node_t)Xmalloc(SIZE_NODE);

	// Set values to members of node
	pnode->data = new_data;

	pnode->parent = NULL;
	pnode->left = NULL;
	pnode->right = NULL;

	return(pnode);
}

static p_node_t locate_node(p_node_t root, data_t e_data, COMPAREDATAPROC pcomparedataproc)
{
	// Code
	p_node_t prunner = root;

	// This Loop Finds the data to be removed
	while(prunner)
	{
		status_t status = pcomparedataproc(e_data, prunner->data);

		if(STATUS_EQUAL == status)
			break;

		if(STATUS_LESSER == status)
		{
			prunner = prunner->left;
		}
		else
		{
			prunner = prunner->right;
		}
	}

	return(prunner);
}

static p_node_t predecessor(p_node_t node)
{
	// Code
	p_node_t prunner = node->left;

	while(prunner->right)
	{
		prunner = prunner->right;
	}

	return(prunner);
}

static p_node_t successor(p_node_t node)
{
	// Code
	p_node_t prunner = node->right;

	while(prunner->left)
	{
		prunner = prunner->left;
	}

	return(prunner);
}

static ret_t generic_tree_insert(tree_t tree, data_t new_data, COMPAREDATAPROC pcomparedataproc)
{
	// Code
	p_node_t prunner = tree->root;

	while(1)
	{
		status_t status = pcomparedataproc(new_data, prunner->data);

		if(STATUS_EQUAL == status)
		{
			ERROR_LOG("Data Already Present");
			return(FAILURE);
		}

		if(STATUS_LESSER == status)
		{
			// Left
			if(NULL == prunner->left)
			{
				// Add new data to left
				prunner->left = create_node(new_data);
				prunner->left->parent = prunner;
				break;
			}

			prunner = prunner->left;
		}
		else
		{
			// Right
			if(NULL == prunner->right)
			{
				// Add new data to right
				prunner->right = create_node(new_data);
				prunner->right->parent = prunner;
				break;
			}

			prunner = prunner->right;
		}
	}

	tree->no_of_elements++;

	return(SUCCESS);
}

static data_t generic_tree_remove(tree_t tree, data_t e_data, COMPAREDATAPROC pcomparedataproc)
{
	// Code
	p_node_t prunner = locate_node(tree->root, e_data, pcomparedataproc);
	// Locate the to be deleted node
	data_t to_return_data = NULL;

	if( NULL == prunner)
	{
		ERROR_LOG("Existing Data Not Found.");
		return((data_t)NULL);
	}

	// Case 1: No Childern Present
	if( NULL == prunner->left && NULL == prunner->right )
	{
		to_return_data = prunner->data;
	}

	// Case 2: prunner have Left Child
	else if( NULL != prunner->left )
	{
		p_node_t p_predessor = predecessor(prunner);

		to_return_data = prunner->data;
		prunner->data = p_predessor->data;

		prunner = p_predessor;
	}

	// Case 3: prunner have Right Child
	else if( NULL != prunner->right )
	{
		p_node_t p_successor = successor(prunner);

		to_return_data = prunner->data;
		prunner->data = p_successor->data;

		prunner = p_successor;
	}

	// Here we do actual removing from tree heirarchy
	if( NULL == prunner->parent )
	{
		tree->root = NULL;
	}
	else if( prunner == prunner->parent->left )
	{
		prunner->parent->left = prunner->right;
		prunner->right->parent = prunner->parent;
	}
	else 
	{
		prunner->parent->right = prunner->left;
		prunner->left->parent = prunner->parent;
	}

	// Here we delete the node
	prunner->data = NULL;
	prunner->left = NULL;
	prunner->right = NULL;
	prunner->parent = NULL;
	free(prunner);
	prunner = NULL;

	tree->no_of_elements--;

	return(to_return_data);
}

static void generic_inorder_recursive(p_node_t node, SHOWDATAPROC pshowdataproc)
{
	// Code
	if(node->left)
		generic_inorder_recursive(node->left, pshowdataproc);

	fprintf(stdout, "{");
	pshowdataproc(node->data);
	fprintf(stdout, "}->");

	if(node->right)
		generic_inorder_recursive(node->right, pshowdataproc);
}

static void generic_preorder_recursive(p_node_t node, SHOWDATAPROC pshowdataproc)
{
	// Code
	fprintf(stdout, "{");
	pshowdataproc(node->data);
	fprintf(stdout, "}->");

	if(node->left)
		generic_preorder_recursive(node->left, pshowdataproc);

	if(node->right)
		generic_preorder_recursive(node->right, pshowdataproc);
}

static void generic_postorder_recursive(p_node_t node, SHOWDATAPROC pshowdataproc)
{
	// Code
	if(node->left)
		generic_postorder_recursive(node->left, pshowdataproc);

	if(node->right)
		generic_postorder_recursive(node->right, pshowdataproc);

	fprintf(stdout, "{");
	pshowdataproc(node->data);
	fprintf(stdout, "}->");
}

static void generic_postorder_delete_recursive(p_node_t node, DELETEDATAPROC pdeletedataproc)
{
	// Code
	if(node->left)
		generic_postorder_delete_recursive(node->left, pdeletedataproc);

	if(node->right)
		generic_postorder_delete_recursive(node->right, pdeletedataproc);

	pdeletedataproc(node->data);	
}

// BST Interface Functions

extern tree_t create_tree()
{
	// Code
	tree_t tree = (tree_t)Xmalloc(SIZE_TREE);

	tree->root = NULL;
	tree->no_of_elements = 0;

	return(tree);
}

// Tree Insert Function
extern ret_t mv_bst_insert(tree_t tree, data_t new_data, COMPAREDATAPROC pcomparedataproc)
{
	// Code
	if(NULL == tree)
	{
		ERROR_LOG("Tree Not Found.");
		return(FAILURE);
	}

	if(NULL == pcomparedataproc)
	{
		ERROR_LOG("Compare callback function must be provided");
		return(FAILURE);
	}

	if(NULL == tree->root)
	{
		tree->root = create_node(new_data);
		tree->no_of_elements++;
	}
	else
	{
		return(generic_tree_insert(tree, new_data, pcomparedataproc));
	}

	return(SUCCESS);
}

// Tree Remove Function
extern data_t mv_bst_remove(tree_t tree, data_t data, COMPAREDATAPROC pcomparedataproc)
{
	// Code
	if( NULL == tree || NULL == tree->root)
	{
		ERROR_LOG("Tree Not Found.");
		return((data_t)NULL);
	}

	if(NULL == pcomparedataproc)
	{
		ERROR_LOG("Compare callback must be provided.");
		return((data_t)NULL);
	}

	return(generic_tree_remove(tree, data, pcomparedataproc));
}

extern void mv_bst_inorder_recursive(tree_t tree, SHOWDATAPROC pshowdataproc)
{
	// Code
	if( NULL == tree || NULL == tree->root )
	{
		ERROR_LOG("Tree Not Found.");
		return;
	}

	if(NULL == pshowdataproc)
	{
		ERROR_LOG("Showdata callback must be provided.");
		return;
	}

	fprintf(stdout, "Tree Inorder Traversal:\n");

	fprintf(stdout, "{Start}->");
	generic_inorder_recursive(tree->root, pshowdataproc);
	fprintf(stdout, "{End}");

	fprintf(stdout, "\n\n");
}

extern void mv_bst_preorder_recursive(tree_t tree, SHOWDATAPROC pshowdataproc)
{
	// Code 
	if( NULL == tree || NULL == tree)
	{
		ERROR_LOG("Tree Not Found.");
		return;
	}

	if(NULL == pshowdataproc)
	{
		ERROR_LOG("Showdata callback must be provided.");
		return;
	}

	fprintf(stdout, "Tree Preorder Traversal:\n");

	fprintf(stdout, "{Start}->");
	generic_preorder_recursive(tree->root, pshowdataproc);
	fprintf(stdout, "{End}");

	fprintf(stdout, "\n\n");
}

extern void mv_bst_postorder_recursive(tree_t tree, SHOWDATAPROC pshowdataproc)
{
	// Code
	if( NULL == tree || NULL == tree)
	{
		ERROR_LOG("Tree Not Found.");
		return;
	}

	if(NULL == pshowdataproc)
	{
		ERROR_LOG("Showdata callback must be provided.");
		return;
	}

	fprintf(stdout, "Tree Postorder Traversal:\n");

	fprintf(stdout, "{Start}->");
	generic_postorder_recursive(tree->root, pshowdataproc);
	fprintf(stdout, "{End}");

	fprintf(stdout, "\n\n");
}

extern  void    mv_bst_inorder_non_recursive(tree_t tree, SHOWDATAPROC pshowdataproc);

extern  void    mv_bst_preorder_non_recursive(tree_t tree, SHOWDATAPROC pshowdataproc);

extern  void    mv_bst_postorder_non_recursive(tree_t tree, SHOWDATAPROC pshowdataproc);


extern  void    mv_bst_destroy_recursive(p_tree_t ptree, DELETEDATAPROC pdeletedataproc)
{
    //   Code
    if( NULL == ptree || NULL == *ptree || NULL == (*ptree)->root )
    {
        ERROR_LOG("Tree Not Found.");
        return;
    }

    if( NULL == pdeletedataproc )
    {
        ERROR_LOG("DeleteData callback must be provided.");
        return;
    }

    fprintf(stdout, "Tree Destroying:\n");
    
    generic_postorder_delete_recursive((*ptree)->root, pdeletedataproc);

    fprintf(stdout, "\n\n");

    free(*ptree);
    *ptree = NULL;
}

extern  void    mv_bst_destroy_non_recursive(p_tree_t ptree, DELETEDATAPROC pdeletedataproc);

