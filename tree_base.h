#ifndef _TREE_BASE_H
#define _TREE_BASE_H

#include "tree_define.h"
#include "tree.h"
#include "tree_operation.h"

/// empty new tree created, root node returns, NULL if failed
Boolean tree_create (struct Tree **tree, tree_type_t type);
/// tree destory, and nodes of tree would also be deleted
void tree_destory (struct Tree **tree);
/// clear tree members, and nodes of tree would also be deleted
Int32 tree_clear (struct Tree **tree);
/// returns numbers of cleared nodes
Boolean tree_is_empty (struct Tree *tree);
/// returns depth of tree (0 is beginning)
Int32 tree_tree_depth (struct Tree *tree);
/// returns distande between most left node and most right node
Int32 tree_tree_width (struct Tree *tree);
/// returns total node counts of tree
Int32 tree_node_count (struct Tree *tree);
/// travserse tree though function visit, traverse stops until visit returns less than 0
void tree_traverse (struct Tree *tree, tree_traverse_t type, Int32 (*visit) (struct tree_node*));
/// returns root node of a tree
struct tree_node* tree_root_of_tree (struct Tree *tree);
/// save tree to file, returns nodes count that have been saved
//* fwrite used, may not be transplantable
Int32 tree_save (struct Tree *tree, const Char* file);
/// load tree struct from file to tree, returns nodes count that have been loaded
//* fread used, may not be transplantable
Int32 tree_load (struct Tree **tree, const Char* file);
/// returns nodes and nodes count of tree with specified depth in left->right order
Int32 tree_depth_nodes (struct Tree *tree, Int32 depth, struct tree_node ***ret);
/// returns nodes and nodes count of tree with max depth of every branch in left->right order
Int32 tree_terminative_nodes (struct Tree *tree, struct tree_node ***ret);
Boolean tree_append_child (struct Tree *tree, struct tree_node *node, struct tree_node *child);
Boolean tree_insert_child (struct Tree *tree, struct tree_node *node, Int32 index, struct tree_node *child);

#endif // _TREE_BASE_H
