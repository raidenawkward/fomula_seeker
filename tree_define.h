#ifndef _TREE_DEFINE_H
#define _TREE_DEFINE_H

#include <stdio.h>

typedef char TreeElement;

typedef enum {
	false = 0,
	true
} Boolean;

typedef char Char;
typedef unsigned char UChar;
typedef unsigned int UInt32;
typedef int Int32;

typedef enum {
	TREE_TYPE_NORMAL =0,
	TREE_TYPE_UNKNOWN
} tree_type_t;


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
