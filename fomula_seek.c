#include "fomula_seek.h"

#include "fomula_seek_define.h"
#include "tree_define.h"

#include "tree.h"
#include "tree_node.h"
#include "tree_base.h"
#include "tree_node_base.h"
#include "tree_operation.h"

#include "used_set.h"
#include "fomula_parse.h"


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

static Boolean init_tree_root_node(struct Tree *tree, struct tree_operations *t_op, Int32 *num_set, Int32 num_count, SeekerOperator *operator_set, Int32 operator_count) {
	if (!tree || !t_op || !num_set || num_count < 0 || !num_set || !operator_set || !num_count || !operator_count)
		return false;
	if (!tree->root)
		return false;

	if (!used_set_init(&(tree->root->data.num_used_set),num_count))
		return false;
	if (!used_set_init(&(tree->root->data.operator_used_set),operator_count))
		return false;

	return true;
}

static Int32 init_operator_set(SeekerOperator** set) {
	Int32 count = OPERA_DIVIDE - OPERA_INVALID;
	*set = (SeekerOperator*)malloc(count * sizeof(SeekerOperator));
	if (!set)
		return -1;
	Int32 i;
	for (i = 0; i < count; ++i)
		(*set)[i] = OPERA_INVALID + i;

	return count;
}

static void constitute_assist_node(struct tree_node *node, struct Tree *tree, struct tree_operations *tree_opt, Int32 *num_set, Int32 num_count, SeekerOperator* operator_set, Int32 operator_count) {
	if (!node || !tree || !tree_opt || !num_set || !operator_set)
		return;
	if (num_count <=0 || operator_count <= 0)
		return;

	if (used_set_unused_num(node->data.num_used_set) == 0)
		return;

	if (node->flag == TNODE_TYPE_ROOT || node->flag == TNODE_TYPE_OPERATOR) {
		Int32 i;
		for (i = used_set_next_unused_index(node->data.num_used_set,-1);
			i >=0 && i < node->data.num_used_set->count;
			i = used_set_next_unused_index(node->data.num_used_set,i)) {
			struct tree_node *child = (struct tree_node*)malloc(sizeof(struct tree_node));
			if (!child)
				return;
			child->parent = node;
			child->childs = NULL;
			child->child_count = 0;
			child->flag = TNODE_TYPE_NUM;
			if (!used_set_init(&child->data.num_used_set,num_count))
				return;
			if (!used_set_init(&child->data.operator_used_set,operator_count))
				return;

			if (!used_set_union(child->data.num_used_set,node->data.num_used_set))
				return;
			if (!used_set_union(child->data.operator_used_set,node->data.operator_used_set))
				return;

			child->data.data = num_set[i];
			child->data.num_used_set->used[i] = true;

			if (!tree_opt->append_child(tree,node,child))
				return;
		}

	} else if (node->flag == TNODE_TYPE_NUM) {
		Int32 i;
		for (i = used_set_next_unused_index(node->data.operator_used_set,-1);
			i >= 0 && i < node->data.operator_used_set->count;
			i =  used_set_next_unused_index(node->data.operator_used_set,i)) {
			struct tree_node *child = (struct tree_node*)malloc(sizeof(struct tree_node));
			if (!child)
				return;
			child->parent = node;
			child->childs = NULL;
			child->child_count = 0;
			child->flag = TNODE_TYPE_OPERATOR;

			if (!used_set_init(&child->data.num_used_set,num_count))
                return;
            if (!used_set_init(&child->data.operator_used_set,operator_count))
                return;

            if (!used_set_union(child->data.num_used_set,node->data.num_used_set))
                return;
            if (!used_set_union(child->data.operator_used_set,node->data.operator_used_set))
                return;

			child->data.data = operator_set[i];
            child->data.operator_used_set->used[i] = true;

            if (!tree_opt->append_child(tree,node,child))
                return;
		}
	}
	else {
		return;
	}

	Int32 i;
	for (i = 0; i < node->child_count; ++i) {
		constitute_assist_node(node->childs[i],tree,tree_opt,num_set,num_count,operator_set,operator_count);
	}
}

static Int32 visit (struct tree_node *node) {
	if (node) {
		Int32 level = 0;
		struct tree_node *parent = node->parent;;
		while(parent) {
			++level;
			parent = parent->parent;
		}
		printf("level : %d, type : %d, node : %d\n",level,node->flag,node->data.data);
	} else
		printf("empty node\n");
	return 1;
}

static Boolean constitute_assist_tree(struct Tree *tree, struct tree_operations *tree_opt, Int32 *num_set, Int32 num_count, SeekerOperator* operator_set, Int32 operator_count) {
	if (!tree || !tree_opt || !num_set || !operator_set)
		return false;
	if (!tree->root || num_count <= 0 || operator_count <= 0)
		return false;

	constitute_assist_node(tree->root,tree,tree_opt,num_set,num_count,operator_set,operator_count);
	return true;
}

static Int32 filter_qualified_tree_nodes(Int32 target, struct tree_node **input, Int32 input_count, struct tree_node ***output) {
	if (!input || !*input)
		return -1;

	if (input_count <= 0)
		return 0;

	
}

Int32 seek_fomula(Int32 target, Int32 *num_set, Int32 num_count, Char*** result) {
	Int32 res_count = 0;

	struct tree_operations *tree_operation = init_tree_operation();
	struct Tree *assistant_tree = create_assistant_tree(tree_operation);
	if (!assistant_tree)
		return -1;

	SeekerOperator *operator_set;
	Int32 operator_count = init_operator_set(&operator_set);
	if (operator_count <= 0)
		return 0;

	if (!init_tree_root_node(assistant_tree,tree_operation,num_set,num_count,operator_set,operator_count))
		return -1;

	if (!constitute_assist_tree(assistant_tree,tree_operation,num_set,num_count,operator_set,operator_count))
		return -1;

	struct tree_node **terminal_tree_nodes;
	Int32 terminal_tree_node_count = tree_operation->terminative_nodes(assistant_tree,&terminal_tree_nodes);

	struct tree_node **qualified_tree_nodes;
	Int32 qualified_tree_node_count = filter_qualified_tree_nodes(target,terminal_tree_nodes, terminal_tree_node_count, &qualified_tree_nodes);

	res_count = qualified_tree_node_count;

	free(operator_set);
	destory_assistant_tree(&assistant_tree,tree_operation);
	free(tree_operation);

	return res_count;
}
