#ifndef _TREE_NODE_H
#define _TREE_NODE_H

#include <stdio.h>
#include "tree_define.h"


struct tree_node {
	TreeElement data;
	struct tree_node** childs;
	struct tree_node* parent;
	Int32 child_count;
	UInt32 flag;
};

/// operations for tree nodes
struct tree_node_operations {
	struct tree_node* (*create) (void);
	struct tree_node* (*get_root) (struct tree_node* node);
	struct tree_node* (*get_parent) (struct tree_node* node);
	Int32 (*child_count) (struct tree_node *node);
	Boolean (*append_child) (struct tree_node *node, struct tree_node *child);
	Boolean (*insert_child) (struct tree_node *node, Int32 index, struct tree_node *child);
	struct tree_node* (*get_first_child) (struct tree_node *node);
	struct tree_node* (*get_last_child) (struct tree_node *node);
	struct tree_node* (*get_child) (struct tree_node *node, Int32 index);
	Int32 (*get_child_index) (struct tree_node *node, struct tree_node *child);
	struct tree_node* (*remove_child) (struct tree_node *node, Int32 index); /// remove node from tree, but returns the node
	struct tree_node* (*get_left_sibling) (struct tree_node *node);
	struct tree_node* (*get_right_sibling) (struct tree_node *node);
	Boolean (*equal_nodes) (struct tree_node *n1, struct tree_node *n2);
	Boolean (*equal_node_data) (TreeElement d1, TreeElement d2);

	Int32 (*free_nodes) (struct tree_node *root); /// free node and its childs
	Int32 (*get_node_largest_depth) (struct tree_node *node, Int32 base); /// get depth of node
	Int32 (*get_node_width) (struct tree_node *node); /// get biggest distance between 2 child nodes
	Int32 (*get_nodes_count) (struct tree_node *node); /// get total count of node and its childs
	Int32 (*depth_priority_traverse) (struct tree_node *node, Int32 (*visit) (struct tree_node*));
	Int32 (*width_priority_traverse) (struct tree_node *node, Int32 (*visit) (struct tree_node*));
	Int32 (*get_node_distance) (struct tree_node *n1, struct tree_node *n2); /// get distance bewteen 2 nodes, -1 returns if unreachable
	Boolean (*is_parent_of) (struct tree_node *n1, struct tree_node *n2); /// returns if n1 is parent of n2
	Boolean (*is_child_of) (struct tree_node *n1, struct tree_node *n2); /// returns if n1 is child of n2
	struct tree_node* (*get_nearest_parent) (struct tree_node *n1, struct tree_node *n2); /// get nearest parent of n1 and n2, NULL returns if not in the same tree
	Int32 (*get_node_depth) (struct tree_node *node); /// get node depth in tree (nodes whose parent is null would be considered as root)
};

#endif // _TREE_NODE_H
