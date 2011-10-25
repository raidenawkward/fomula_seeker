#ifndef _TREE_DEFINE_H
#define _TREE_DEFINE_H

#include "cross_define.h"
#include <stdio.h>
#include "fomula_seek_define.h"


typedef enum {
	TREE_TYPE_NORMAL =0,
	TREE_TYPE_UNKNOWN
} tree_type_t;


struct assist_tree_element {
    struct used_set *num_used_set;
    struct used_set *operator_used_set;
	UChar data;
};

typedef struct assist_tree_element TreeElement;

typedef enum {
	TREE_TRAVERSE_PREORDER =0,
	TREE_TRAVERSE_INORDER,
	TREE_TRAVERSE_POSTORDER,
	////////////////////////////
	TREE_TRAVERSE_DEPTHPRIORITY,
	TREE_TRAVERSE_WIDTHPRIORITY,
	TREE_TRAVERSE_ROUTE, /// traverse every branch from root node
	TREE_TRAVERSE_OTHERORDER
} tree_traverse_t;


#endif // _TREE_DEFINE_H
