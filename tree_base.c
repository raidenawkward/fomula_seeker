#include "tree_base.h"

#include <stdio.h>
#include <stdlib.h>

Boolean tree_create (struct Tree **tree, tree_type_t type) {
	*tree = (struct Tree*)malloc(sizeof(struct Tree));
	if (!(*tree))
		return false;

	(*tree)->root = NULL;

	struct tree_node_operations *node_op = treenode_get_operation();
	(*tree)->node_opera = node_op;

	(*tree)->type = type;
	(*tree)->max_child_count_of_node = -1;

	return true;
}

void tree_destory (struct Tree **tree) {
	tree_clear(tree);
	if (*tree)
		free(*tree);
}

static Int32 free_tree_node(struct tree_node *node) {
	if (!node)
		return 0;

	Int32 ret = 1,i;

	for (i = 0; i < node->child_count; ++i) {
		struct tree_node *child = node->childs[i];
		ret += free_tree_node(child);
	}
	for (i = 0; i < node->child_count; ++i) {
		free(node->childs[i]);
	}
	node->child_count = 0;
	return ret;
}

Int32 tree_clear (struct Tree **tree) {
	Int32 ret = 0;
	if (!tree || !(*tree))
		return ret;
	if (!(*tree)->root)
		return ret;
	if ((*tree)->node_opera)
		ret = (*tree)->node_opera->free_node((*tree)->root);
	else
		ret = free_tree_node((*tree)->root);
	(*tree)->root = NULL;
	return ret;
}

Boolean tree_is_empty (struct Tree *tree) {
	Boolean ret = false;
	if (!tree)
		return ret;

	if (!tree->root)
		return ret;

	ret = true;
	return ret;
}

static Int32 traverse_for_depth(struct tree_node *node,Int32 depth) {
	if (!node)
		return depth;
	Int32 i,ret = depth;
	for (i = 0; i < node->child_count; ++i) {
		Int32 new_ret = traverse_for_depth(node->childs[i],depth + 1);
		if (new_ret > ret)
			ret = new_ret;
	}

	return ret;
}

Int32 tree_tree_depth (struct Tree *tree) {
	Int32 ret = 0;
	if (!tree)
		return -1;
	if (!tree->root)
		return ret;

	if (tree->node_opera)
		ret = tree->node_opera->get_node_largest_depth(tree->root,0);
	else
		ret = traverse_for_depth(tree->root,0);

	return ret;
}

Int32 tree_tree_width(struct Tree *tree) {
	if (!tree)
		return -1;
	if (!tree->node_opera)
		return -1;
	if (!tree->root)
		return 0;
	return tree->node_opera->get_node_width(tree->root);
}

static Int32 get_node_child_nodes(struct tree_node *node) {
	if (!node)
		return 0;
	Int32 ret = 1,i;
	for (i = 0; i < node->child_count; ++i) {
		ret += get_node_child_nodes(node->childs[i]);
	}
	return ret;
}

Int32 tree_node_count (struct Tree *tree) {
	Int32 ret = 0;
	if (!tree)
		return ret;
	if (!tree->root)
		return ret;
	if (tree->node_opera)
		ret = tree->node_opera->get_nodes_count(tree->root);
	else
		ret = get_node_child_nodes(tree->root);
	return ret;
}

static Int32 depth_priority_traverse(struct tree_node *node, Int32 (*visit) (struct tree_node*)) {
	if (!node || !visit)
		return -1;
	Int32 i;

	if (visit(node) < 0)
		return -1;

	for (i = 0; i < node->child_count; ++i) {
		if (depth_priority_traverse(node->childs[i],visit) < 0)
			return -1;
	}
	return 1;
}

static Int32 width_priority_traverse(struct tree_node *node, Int32 (*visit) (struct tree_node*)) {
	if (!node || !visit)
		return -1;

	Int32 i;
	for (i = 0; i < node->child_count; ++i) {
		if (visit(node->childs[i]) < 0)
			return -1;
	}

	for (i = 0; i < node->child_count; ++i) {
		if (width_priority_traverse(node->childs[i], visit) < 0)
			return -1;
	}
	return 1;
}

static void route_traverse(struct Tree *tree, Int32 (*visit) (struct tree_node *)) {
	if (!tree || !visit)
		return;
	if (!tree->root)
		return;

	struct tree_node **term_nodes, **path_nodes = NULL;
	Int32 path_length = 0;
	Int32 term_count = tree_terminative_nodes(tree,&term_nodes);
	Int32 i;
	struct tree_node *cur_node = NULL;

	for (i = 0; i < term_count; ++i) {
		cur_node = term_nodes[i];
		while (cur_node) {
			if (!path_length) {
				path_nodes = (struct tree_node**)malloc(sizeof(struct tree_node*));
				if (!path_nodes)
					goto done;
			} else {
				struct tree_node **new_ptr = (struct tree_node**)realloc(path_nodes,sizeof(struct tree_node*) * (path_length + 1));
				if (!path_nodes)
					goto done;
				path_nodes = new_ptr;
			}
			++ path_length;
			path_nodes[path_length - 1] = (struct tree_node*)malloc(sizeof(struct tree_node*));
			if (!path_nodes[path_length - 1])
				goto done;
			path_nodes[path_length - 1] = cur_node;
			cur_node = cur_node->parent;
		} // while

		Int32 j;
		for (j = path_length - 1; j >= 0; --j) {
			if (!visit(path_nodes[j])) {
				break;
			}
		}
#if 0 // +_+
		for (j = 0; j < path_length; ++j) {
			free(path_nodes[j]);
		}
#endif
		path_length = 0;
		free(path_nodes);
	} // for

done:
#if 0 // +_+
	for (i = 0; i < term_count; ++i) {
		free(term_nodes[i]);
	}
#endif
	free(term_nodes);
}

void tree_traverse (struct Tree *tree, tree_traverse_t type, Int32 (*visit) (struct tree_node*)) {
	if (!tree)
		return;
	if (!tree->root)
		return;
	switch (type) {
	case TREE_TRAVERSE_DEPTHPRIORITY:
		if (tree->node_opera)
			tree->node_opera->depth_priority_traverse(tree->root,visit);
		else
			depth_priority_traverse(tree->root,visit);
		break;
	case TREE_TRAVERSE_WIDTHPRIORITY:
		if (!visit(tree->root))
			return;
		if (tree->node_opera)
			tree->node_opera->width_priority_traverse(tree->root,visit);
		else
			width_priority_traverse(tree->root,visit);
		break;
	case TREE_TRAVERSE_ROUTE:
		route_traverse(tree,visit);
		break;
	default:
		break;
	}
}

struct tree_node* tree_root_of_tree (struct Tree *tree) {
	if (!tree)
		return NULL;
	return tree->root;
}

static Boolean save_tree_node(FILE* fp, struct tree_node *node) {
	if (!fp || !node)
		return false;
	if (!fwrite(node,sizeof(struct tree_node),1,fp))
		return false;
	return true;
}

/// save tree struct
static Boolean save_tree_head(FILE* fp, struct Tree *tree) {
	if (!fp || !tree)
		return false;
	if (!fwrite(tree,sizeof(struct Tree),1,fp))
		return false;
	return true;
}

static Int32 save_node_childs_recursively(FILE* fp, struct tree_node *root) {
	if (!root || !fp)
		return 0;
	Int32 i,ret = 0;

	for (i = 0; i < root->child_count; ++i) {
		if (save_tree_node(fp,root->childs[i]))
			++ ret;
	}

	for (i = 0; i < root->child_count; ++i) {
		ret += save_node_childs_recursively(fp,root->childs[i]);
	}

	return ret;
}

Int32 tree_save (struct Tree *tree, const Char* file) {
	Int32 ret = 0;
	if (!tree)
		return ret;
	if (!tree->root)
		return ret;

	FILE* fp = fopen(file,"w+");
	if (!fp)
		return ret;

	if (!save_tree_head(fp,tree))
		goto done;

	ret += save_tree_node(fp,tree->root);
	ret += save_node_childs_recursively(fp, tree->root);

done:
	fclose(fp);
	return ret;
}

/// read tree struct
static Boolean read_tree_head(FILE* fp, struct Tree **tree) {
	if (!fp)
		return false;
	if (fseek(fp,0L,SEEK_SET) < 0)
		return false;

	*tree = (struct Tree*)malloc(sizeof(struct Tree));
	if (!tree)
		return false;

	if (!fread(*tree,sizeof(struct Tree),1,fp)) {
		free(*tree);
		return false;
	}

	(*tree)->node_opera = treenode_get_operation();
	return true;
}

static int read_node_childs_recursively (FILE* fp, struct tree_node *root) {
	if (!fp || !root)
		return 0;

	Int32 i,ret = 0;
	for (i = 0; i < root->child_count; ++i) {
		struct tree_node *child = (struct tree_node*)malloc(sizeof(struct tree_node));
		if (!child)
			break;
		if 	(!fread(child,sizeof(struct tree_node),1,fp)) {
			free(child);
			break;
		}
		root->childs[i] = child;
		++ret;
	}

	for (i = 0; i < root->child_count; ++i) {
		ret += read_node_childs_recursively(fp,root->childs[i]);
	}

	return ret;
}

Int32 tree_load (struct Tree **tree, const Char* file) {
	if (!file)
		return 0;
	FILE *fp = fopen(file,"r+");
	if (!fp)
		return 0;

	Int32 ret = 0;

	if (!read_tree_head(fp,tree))
		goto done;

	// root node
	struct tree_node *root = (struct tree_node*)malloc(sizeof(struct tree_node));
	if (!root)
		goto done;
	if (!fread(root,sizeof(struct tree_node),1,fp))
		goto done;
	root->parent = NULL;
	(*tree)->root = root;
	ret += 1;

	ret += read_node_childs_recursively(fp,root);

done:
	fclose(fp);
	return ret;
}

static Int32 depth_nodes_private(struct tree_node *node, Int32 current_depth, Int32 target_depth, struct tree_node ***ret_ptr, Int32 *ret_count) {
	if (!node || current_depth > target_depth)
		return 0;

	if (current_depth == target_depth) {
		struct tree_node **new_ptr;
		if (*ret_count <= 0) {
			*ret_count = 0;
			new_ptr = (struct tree_node**)malloc(sizeof(struct tree_node*));
		} else
			new_ptr = (struct tree_node**)realloc(*ret_ptr,sizeof(struct tree_node*) * ((*ret_count) + 1));

		if (new_ptr) {
			++ (*ret_count);
			*ret_ptr = new_ptr;
			(*ret_ptr)[(*ret_count) - 1] = (struct tree_node*)malloc(sizeof(struct tree_node*));
			if ((*ret_ptr)[(*ret_count) - 1]) {
				(*ret_ptr)[(*ret_count) - 1] = node;
			} else {
				--(*ret_count);
			}
		}
	} else if (current_depth < target_depth) {
		Int32 i;
		for (i = 0; i < node->child_count; ++i) {
			depth_nodes_private(node->childs[i], current_depth + 1, target_depth, ret_ptr, ret_count);
		}
	}

	return 1;
}

Int32 tree_depth_nodes (struct Tree *tree, Int32 depth, struct tree_node ***ret) {
	if (!tree)
		return 0;
	if (!tree->root)
		return 0;
	Int32 ret_count = 0;
	depth_nodes_private(tree->root,0,depth,ret,&ret_count);

	return ret_count;
}

Int32 terminative_nodes_private(struct tree_node *node, struct tree_node ***ret_ptr, Int32 *ret_count) {
	if (!node)
		return -1;
	if (node->child_count <= 0 || !node->childs) { // hit
		struct tree_node **new_ptr = NULL;
		if (*ret_count <= 0) {
			*ret_count = 0;
			new_ptr = (struct tree_node**)malloc(sizeof(struct tree_node*));
		} else {
			new_ptr = (struct tree_node**)realloc(*ret_ptr,sizeof(struct tree_node*) * (*ret_count + 1));
		}

		if (new_ptr) {
			++ *ret_count;
			*ret_ptr = new_ptr;
			(*ret_ptr)[(*ret_count) - 1] = (struct tree_node*)malloc(sizeof(struct tree_node*));
			if ((*ret_ptr)[(*ret_count) - 1]) {
                (*ret_ptr)[(*ret_count) - 1] = node;
            } else {
               --(*ret_count);
            }
		}
		return 1;
	} else {
		Int32 i;
		for (i = 0; i < node->child_count; ++i) {
			terminative_nodes_private(node->childs[i],ret_ptr,ret_count);
		}
	}
	return 0;
}

Int32 tree_terminative_nodes (struct Tree *tree, struct tree_node ***ret) {
	if (!tree)
		return 0;
	if (!tree->root)
		return 0;

	Int32 ret_count = 0;
	terminative_nodes_private(tree->root,ret,&ret_count);
	return ret_count;
}

Boolean tree_append_child (struct Tree *tree, struct tree_node *node, struct tree_node *child) {
	if (!tree || !node)
		return false;

	if (!tree->node_opera)
		return false;
	if (!tree->node_opera->append_child)
		return false;

	if (tree->max_child_count_of_node <= node->child_count)
		return false;

	return tree->node_opera->append_child(node,child);
}

Boolean tree_insert_child (struct Tree *tree, struct tree_node *node, Int32 index, struct tree_node *child) {
	if (!tree || !node)
		return false;

	if (!tree->node_opera)
		return false;
	if (!tree->node_opera->insert_child)
		return false;

	if (tree->max_child_count_of_node <= node->child_count)
		return false;

	return tree->node_opera->insert_child(node,index,child);
}


