#include "fomula_seeker.h"

#include "fomula_seeker_define.h"
#include "tree_define.h"

#include "tree.h"
#include "tree_node.h"

#include "tree_base.h"
#include "tree_node_base.h"
#include "tree_operation.h"

#include "used_set.h"


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
}

static Boolean init_tree_root_node(struct Tree *tree, struct tree_operations *t_op, Int32 *num_set, Int32 num_count) {
	if (!tree || !t_op || !num_set || num_count < 0)
		return false;
	if (!tree->root)
		return false;

	Int32 i;
	for (i = 0; i < num_count; ++i) {
		struct tree_node *node = (struct tree_node*)malloc(sizeof(struct tree_node));
		if (!node)
			return false;

		node->data = num_set[i];
		node->flag = TNODE_TYPE_NUM;
		if (!t_op->append_child(tree,tree->root,node))
			return false;
	}

	return true;
}

static Int32 init_operator_set(SeekerOperator** set) {
	Int32 count = OPERA_DIVIDE - OPERA_INVALID + 1;
	*set = (SeekerOperator*)malloc(count * sizeof(SeekerOperator));
	if (!set)
		return -1;
	Int32 i;
	for (i = 0; i < count; ++i)
		(*set)[i] = OPERA_INVALID + i;

	return count;
}

static Boolean next_unused_operator(SeekerOperator *operator_set, Boolean *used_set, SeekerOperator *result) {
	return false;
}

static Boolean next_unused_number(Int32 *num_set, Boolean *used_set, Int32 *result) {
	return false;
}

Int32 seek_fomula(Int32 target, Int32 *num_set, Int32 num_count, Char*** result) {
	Int32 res_count = 0;

	struct tree_operations *tree_operation = init_tree_operation();
	struct Tree *assistant_tree = create_assistant_tree(tree_operation);
	if (!assistant_tree)
		return -1;

	if (!init_tree_root_node(assistant_tree,tree_operation,num_set,num_count))
		return -1;

	SeekerOperator *operator_set;
	Int32 operator_count = init_operator_set(&operator_set);
	if (operator_count <= 0)
		return 0;

	struct used_set *num_used_set, *operator_used_set;
	if (!used_set_init(&num_used_set,num_count))
		return -1;
	if (!used_set_init(&operator_used_set,operator_count))
		return -1;


	used_set_destory(&num_used_set);
	used_set_destory(&operator_used_set);
	free(operator_set);
	destory_assistant_tree(&assistant_tree,tree_operation);
	free(tree_operation);

	return res_count;
}
