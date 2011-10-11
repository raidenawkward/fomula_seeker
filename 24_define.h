#ifndef _24_DEFINE_H
#define _24_DEFINE_H

#include <stdlib.h>

#define MAX_TREE_CHILD_NODE 1024;

typedef enum {
	OPERA_INVALID = 0,
	OPERA_PLUS,
	OPERA_SUBTRACT,
	OPERA_MULTIPLE,
	OPERA_DIVIDE
} operator_24;

typedef enum {
	TNODE_TYPE_UNKNOWN = 0,
	TNODE_TYPE_ROOT,
	TNODE_TYPE_NUM,
	TNODE_TYPE_OPERATOR
} tree_node_type_24;

#endif // _24_DEFINE_H
