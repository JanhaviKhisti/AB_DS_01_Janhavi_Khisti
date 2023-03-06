
// Headers
#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_avl.h"

tree_t	tree = NULL;

status_t	compare_data(data_t data1, data_t data2)
{
	// Code
	if( (long long)data1 == (long long)data2 )
		return(STATUS_EQUAL);
	else if( (long long)data1 < (long long)data2 )
		return(STATUS_LESSER);
	else 
		return(STATUS_GREATER);
}

void	show_data(data_t data)
{
	// Code
	fprintf(stdout, "%lld", (long long)data);
}

void	delete_data(data_t data)
{
	// Code
	fprintf(stdout, "%lld", (long long)data);
}

int main(void)
{
	// Code

	tree = create_tree();

	/*mv_avl_insert(tree, (data_t)(long long)10, compare_data);
	mv_avl_insert(tree, (data_t)(long long)20, compare_data);
	mv_avl_insert(tree, (data_t)(long long)30, compare_data);
	mv_avl_insert(tree, (data_t)(long long)40, compare_data);
	mv_avl_insert(tree, (data_t)(long long)50, compare_data);*/

	for( int le = 0; le < 50; ++le )
		mv_avl_insert(tree, (data_t)(long long)((le+1)*10), compare_data);



	//mv_avl_inorder_recursive(tree, show_data);
	mv_avl_inorder_non_recursive(tree, show_data);

	//mv_avl_preorder_recursive(tree, show_data);
	mv_avl_preorder_non_recursive(tree, show_data);
	
	//mv_avl_postorder_recursive(tree, show_data);
	mv_avl_postorder_non_recursive(tree, show_data);

	/*printf("Removed Data :");
	delete_data( mv_avl_remove(tree, (data_t)(long long)50, compare_data) );
	printf("\n");
	printf("Removed Data :");
	delete_data( mv_avl_remove(tree, (data_t)(long long)10, compare_data) );
	printf("\n\n");

	//mv_avl_inorder_recursive(tree, show_data);
	mv_avl_inorder_non_recursive(tree, show_data);

	//mv_avl_preorder_recursive(tree, show_data);
	mv_avl_preorder_non_recursive(tree, show_data);
	
	//mv_avl_postorder_recursive(tree, show_data);
	mv_avl_postorder_non_recursive(tree, show_data);*/

	mv_avl_destroy_non_recursive(&tree, delete_data);

	exit(SUCCESS);
}

