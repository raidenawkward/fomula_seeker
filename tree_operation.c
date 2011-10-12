#include "tree_operation.h"

struct tree_operations* tree_get_operation() {
	struct tree_operations *op = (struct tree_operations*)malloc(sizeof(struct tree_operations));
	if (!op)
		return NULL;
	op->create = tree_create;
	op->destory = tree_destory;
	op->clear = tree_clear;
	op->is_empty = tree_is_empty;
	op->tree_depth = tree_tree_depth;
	op->tree_width = tree_tree_width;
	op->node_count = tree_node_count;
	op->traverse = tree_traverse;
	op->root_of_tree = tree_root_of_tree;
	op->save = tree_save;
	op->load = tree_load;
	op->depth_nodes = tree_depth_nodes;
	op->terminative_nodes = tree_terminative_nodes;
	op->insert_child = tree_insert_child;
	op->append_child = tree_append_child;
	
	return op;
}

struct tree_node_operations* treenode_get_operation() {
	struct tree_node_operations *op = (struct tree_node_operations*)malloc(sizeof(struct tree_node_operations));
	if (!op)
		return NULL;

	op->get_root = treenode_get_root;
	op->get_parent = treenode_get_parent;
	op->child_count = treenode_child_count;
	op->append_child = treenode_append_child;
	op->insert_child = treenode_insert_child;
	op->get_first_child = treenode_get_first_child;
	op->get_last_child = treenode_get_last_child;
	op->get_child = treenode_get_child;
	op->get_child_index = treenode_get_child_index;
	op->remove_child = treenode_remove_child;
	op->get_left_sibling = treenode_get_left_sibling;
	op->get_right_sibling = treenode_get_right_sibling;
	op->equal_node = treenode_equal_node;
	op->free_node = treenode_free_node;
	op->get_node_largest_depth = treenode_get_node_largest_depth;
	op->get_node_width = treenode_get_node_width;
	op->get_nodes_count = treenode_get_nodes_count;
	op->depth_priority_traverse = treenode_depth_priority_traverse;
	op->width_priority_traverse = treenode_width_priority_traverse;
	op->get_node_distance = treenode_get_node_distance;
	op->is_parent_of = treenode_is_parent_of;
	op->is_child_of = treenode_is_child_of;
	op->get_nearest_parent = treenode_get_nearest_parent;
	op->get_node_depth = treenode_get_node_depth;
	return op;
}
