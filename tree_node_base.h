#ifndef _TREE_NODE_BASE_H
#define _TREE_NODE_BASE_H

#include <stdio.h>
#include <stdlib.h>
#include "tree_define.h"
#include "tree_node.h"

/// create new node
struct tree_node* treenode_create();
/// get root node from a node
struct tree_node* treenode_get_root (struct tree_node* node);
/// get parent node of a node
struct tree_node* treenode_get_parent (struct tree_node* node);
/// get child count of a node
Int32 treenode_child_count (struct tree_node *node);
/// append node 'child' as last child of target node, true returns if suddeed
Boolean treenode_append_child (struct tree_node *node, struct tree_node *child);
/// insert node 'child' to target node as index, true returns if suddeed
Boolean treenode_insert_child (struct tree_node *node, Int32 index, struct tree_node *child);
/// get first child of node
struct tree_node* treenode_get_first_child (struct tree_node *node);
/// get last child of node
struct tree_node* treenode_get_last_child (struct tree_node *node);
/// get index child of node
struct tree_node* treenode_get_child (struct tree_node *node, Int32 index);
/// get index of child node from parent node, -1 returns if not found
Int32 treenode_get_child_index (struct tree_node *node, struct tree_node *child);
/// remove node from node, but returns the node that was removed from node
struct tree_node* treenode_remove_child (struct tree_node *node, Int32 index);
/// get left sibling of node in parent node
struct tree_node* treenode_get_left_sibling (struct tree_node *node);
/// get right sibling of node in parent node
struct tree_node* treenode_get_right_sibling (struct tree_node *node);
/// compare tree nodes content from different addrs
Boolean treenode_equal_nodes (struct tree_node *n1, struct tree_node *n2);
Boolean treenode_equal_node_data (TreeElement d1, TreeElement d2);
/// free node and its childs
Int32 treenode_free_nodes (struct tree_node *root);
/// get depth of node
Int32 treenode_get_node_largest_depth (struct tree_node *node, Int32 base_depth);
//// get distance between most left node and most right node
Int32 treenode_get_node_width (struct tree_node *node);
/// get total count of node and its childs
Int32 treenode_get_nodes_count (struct tree_node *node);
Int32 treenode_depth_priority_traverse (struct tree_node *node, Int32 (*visit) (struct tree_node*));
Int32 treenode_width_priority_traverse (struct tree_node *node, Int32 (*visit) (struct tree_node*));
/// get distance between n1 and n2, -1 returns if not in the same tree
Int32 treenode_get_node_distance (struct tree_node *n1, struct tree_node *n2);
/// returns if n1 is parent of n2
Boolean treenode_is_parent_of (struct tree_node *n1, struct tree_node *n2);
/// returns if n1 is child of n2
Boolean treenode_is_child_of (struct tree_node *n1, struct tree_node *n2);
///  get nearest parent of n1 and n2, NULL returns if not in the same tree
struct tree_node* treenode_get_nearest_parent (struct tree_node *n1, struct tree_node *n2);
/// get node depth in tree (nodes whose parent is null would be considered as root)
Int32 treenode_get_node_depth (struct tree_node *node);

#endif // _TREE_NODE_BASE_H
