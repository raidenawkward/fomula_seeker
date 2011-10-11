#ifndef _TREE_OPERATION_H
#define _TREE_OPERATION_H

#include "tree.h"
#include "tree_base.h"
#include "tree_node.h"
#include "tree_node_base.h"

struct tree_operations* tree_get_operation();
struct tree_node_operations* treenode_get_operation();

#endif // _TREE_OPERATION_H
