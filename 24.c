#include "24.h"

#include "24_define.h"
#include "tree_define.h"

#include "tree.h"
#include "tree_node.h"

#include "tree_base.h"
#include "tree_node_base.h"
#include "tree_operation.h"

static struct tree_operations *init_tree_operation() {
	struct tree_operations *tree_op = tree_get_operation();
	return tree_op;
}

static struct Tree* create_assistant_tree(struct tree_operations* t_op) {
	if (!t_op)
		return NULL;

	struct Tree *tree = NULL;
	struct tree_node_operations *node_op = treenode_get_operation();
	if (!node_op)
		return NULL;
	if (!t_op->create(&tree,TREE_TYPE_NORMAL))
		return NULL;
	if (!tree)
		return NULL;

	struct tree_node *root = (struct tree_node*)malloc(sizeof(struct tree_node));
	if (!root)
		return NULL;
	root->parent = NULL;
	root->childs = NULL;
	root->child_count = 0;
	root->flag = TNODE_TYPE_ROOT;
	root->data = OPERA_INVALID;

	tree->root = root;
	tree->node_opera = node_op;
	tree->max_child_count_of_node = MAX_TREE_CHILD_NODE;

	return tree;
}

static void destory_assistant_tree(struct Tree **tree, struct tree_operations *t_op) {
	if (!tree || !t_op)
		return;
	if (!tree)
		return;
	t_op->destory(tree);
	free(t_op);
}

static Boolean init_tree_root_node(struct Tree *tree, struct tree_operations *t_op, Int32 *num, Int32 num_count) {
	if (!tree || !t_op || !num || num_count < 0)
		return false;
	if (!tree->root)
		return false;

	Int32 i;
	for (i = 0; i < num_count; ++i) {
		struct tree_node *node = (struct tree_node*)malloc(sizeof(struct tree_node));
		if (!node)
			return false;

		node->data = num[i];
		node->flag = TNODE_TYPE_NUM;
		if (!t_op->append_child(tree,tree->root,node))
			return false;
	}

	return true;
}

Int32 seek_24_fomula(Int32 *num, Int32 num_count, Char*** result) {
	Int32 res_count = 0;

	struct tree_operations *tree_operation = init_tree_operation();
	struct Tree *assistant_tree = create_assistant_tree(tree_operation);
	if (!assistant_tree)
		return -1;

	if (!init_tree_root_node(assistant_tree,tree_operation,num,num_count))
		return -1;


	destory_assistant_tree(&assistant_tree,tree_operation);

	return res_count;
}
