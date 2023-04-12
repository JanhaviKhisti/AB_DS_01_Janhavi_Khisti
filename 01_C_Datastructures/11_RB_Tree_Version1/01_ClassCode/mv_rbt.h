
// Conditional Compilation

#ifndef _MV_RBT_H
#define _MV_RBT_H

#ifndef SUCCESS 
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE 1
#endif

#define RED 0
#define BLACK 1

// Typedefs
struct mv_rbt;

typedef struct mv_rbt*  tree_t;
typedef struct mv_rbt** p_tree_t;

struct tree_node;

typedef struct tree_node   tree_node_t;
typedef struct tree_node*  p_tree_node_t;
typedef struct tree_node** pp_tree_node_t;

typedef void* data_t;
typedef int ret_t;
typedef int status_t;
typedef char color_t;

typedef status_t(*COMPAREDATAPROC)(data_t, data_t);
typedef void(*SHOWDATAPROC)(data_t);
typedef void(*DELETEDATAPROC)(data_t);

// struct type definitions
struct mv_rbt
{
	p_tree_node_t root;
	size_t no_of_elements;
};
#define SIZE_TREE (sizeof(struct mv_rbt))

struct tree_node
{
	data_t data;
	color_t color;

	p_tree_node_t parent;
	p_tree_node_t left;
	p_tree_node_t right;
};
#define SIZE_TREE_NODE (sizeof(struct tree_node))

enum
{
	STATUS_NONE = 0,
	STATUS_EQUAL,
	STATUS_LESSER,
	STATUS_GREATER
};

// BST Interface Functions
extern tree_t create_tree();

// Tree Insert Function
extern ret_t mv_rbt_insert(tree_t tree, data_t new_data, COMPAREDATAPROC pcomparedataproc);

// Tree Removal Function
extern data_t mv_rbt_remove(tree_t tree, data_t data, COMPAREDATAPROC pcomparedataproc);

// Tree Traversal Functions
extern void mv_rbt_inorder_recursive(tree_t tree, SHOWDATAPROC pshowdataproc);
extern void mv_rbt_preorder_recursive(tree_t tree, SHOWDATAPROC pshowdataproc);
extern void mv_rbt_postorder_recursive(tree_t tree, SHOWDATAPROC pshowdataproc);

extern void mv_rbt_inorder_non_recursive(tree_t tree, SHOWDATAPROC pshowdataproc);
extern void mv_rbt_preorder_non_recursive(tree_t tree, SHOWDATAPROC pshowdataproc);
extern void mv_rbt_postorder_non_recursive(tree_t tree, SHOWDATAPROC pshowdataproc);

extern void mv_rbt_destroy_recursive(p_tree_t ptree, DELETEDATAPROC pdeletedataproc);
extern void mv_rbt_destroy_non_recursive(p_tree_t ptree, DELETEDATAPROC pdeletedataproc);

#endif /* _MV_RBT_H */


