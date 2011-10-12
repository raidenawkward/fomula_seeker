#include "tree_node_base.h"

struct tree_node* treenode_get_root (struct tree_node* node) {
	if (!node)
		return NULL;
	struct tree_node* ret = node->parent;
	while (ret) {
		if (ret->parent)
			ret = ret->parent;
		else
			break;
	}
	return ret;
}

struct tree_node* treenode_get_parent (struct tree_node* node) {
	if (!node)
		return NULL;
	return node->parent;
}

Int32 treenode_child_count (struct tree_node *node) {
	if (!node)
		return 0;
	return node->child_count;
}

Boolean treenode_append_child (struct tree_node *node, struct tree_node *child) {
	if (!node)
		return false;
	return treenode_insert_child(node,node->child_count,child);
}

Boolean treenode_insert_child (struct tree_node *node, Int32 index, struct tree_node *child) {
	Boolean ret = false;
	if (!node || !child)
		return ret;
	if (index < 0
		|| node->child_count < 0
		|| index > node->child_count)
		return ret;

	struct tree_node **new_base;
	if (node->child_count <= 0) {
		node->child_count = 0;
		new_base = (struct tree_node**)malloc(sizeof(struct tree_node*));
	} else {
		new_base = (struct tree_node**)realloc(node->childs,(node->child_count + 1) * sizeof(struct tree_node*));
	}

	if (!new_base)
		return ret;
	node->childs = new_base;
	++ node->child_count;
	Int32 i;
	for (i = node->child_count - 1; i > index; --i) {
		node->childs[i] = node->childs[i - 1];
	}
	node->childs[index] = child;
	child->parent = node;

	ret = true;
	return ret;
}

struct tree_node* treenode_get_last_child (struct tree_node *node) {
	if (!node)
		return NULL;
	return treenode_get_child(node,node->child_count - 1);
}

struct tree_node* treenode_get_first_child (struct tree_node *node) {
	return treenode_get_child(node,0);
}

struct tree_node* treenode_get_child (struct tree_node *node, Int32 index) {
	if (!node)
		return NULL;
	if (index < 0 || index >= node->child_count)
		return NULL;

	return node->childs[index];
}

Int32 treenode_get_child_index (struct tree_node *node, struct tree_node *child) {
	Int32 ret = -1;
	if (!node || !child)
		return ret;

	Int32 i;
	for (i = 0; i < node->child_count; ++i) {
		struct tree_node *n = node->childs[i];
		if (treenode_equal_node(n,child)) {
			ret = i;
			break;
		}
	}
	return ret;
}

struct tree_node* treenode_remove_child (struct tree_node *node, Int32 index) {
	if (!node)
		return NULL;
	if (index < 0 || index >= node->child_count)
		return NULL;

	struct tree_node *ret = node->childs[index];
	Int32 i;
	for (i = index; i < node->child_count - 1; ++i) {
		node->childs[i] = node->childs[i + 1];
	}
	-- node->child_count;

	return ret;
}

struct tree_node* treenode_get_left_sibling (struct tree_node *node) {
	if (!node)
		return NULL;
	if (!node->parent)
		return NULL;

	Int32 index = treenode_get_child_index(node->parent, node);
	return treenode_get_child(node->parent,index - 1);
}

struct tree_node* treenode_get_right_sibling (struct tree_node *node) {
	if (!node)
		return NULL;
	if (!node->parent)
		return NULL;

	Int32 index = treenode_get_child_index(node->parent, node);
	return treenode_get_child(node->parent,index + 1);
}

Boolean treenode_equal_node (struct tree_node *n1, struct tree_node *n2) {
	Boolean ret = false;
	if (!n1 || !n2) {
		if (n1 == n2)
			return true;
		return ret;
	}

	if (n1->flag != n2->flag)
		return ret;
	if (n1->parent != n2->parent)
		return ret;
	if (n1->child_count != n2->child_count)
		return ret;
	//if (n1->data != n2->data)
	//	return ret;
	if (n1->childs != n2->childs)
		return ret;

	ret = true;
	return ret;
}

Int32 treenode_free_node (struct tree_node *node) {
	if (!node)
		return 0;

	Int32 ret = 1,i;

	for (i = 0; i < node->child_count; ++i) {
		struct tree_node *child = node->childs[i];
		ret += treenode_free_node(child);
	}
	for (i = 0; i < node->child_count; ++i) {
		free(node->childs[i]);
	}
	node->child_count = 0;
	return ret;
}

Int32 treenode_get_node_largest_depth (struct tree_node *node, Int32 depth) {
	if (!node)
		return depth;
	Int32 i,ret = depth;
	for (i = 0; i < node->child_count; ++i) {
		Int32 new_ret = treenode_get_node_largest_depth(node->childs[i],depth + 1);
		if (new_ret > ret)
			ret = new_ret;
	}

	return ret;
}

Int32 treenode_get_node_width (struct tree_node *node) {
	return -1;
}

Int32 treenode_get_nodes_count (struct tree_node *node) {
	if (!node)
		return 0;
	Int32 ret = 1,i;
	for (i = 0; i < node->child_count; ++i) {
		ret += treenode_get_nodes_count(node->childs[i]);
	}
	return ret;
}

Int32 treenode_depth_priority_traverse (struct tree_node *node, Int32 (*visit) (struct tree_node*)) {
	if (!node)
		return -1;
	Int32 i;

	if (visit(node) < 0)
		return -1;

	for (i = 0; i < node->child_count; ++i) {
		if (treenode_depth_priority_traverse(node->childs[i],visit) < 0)
			return -1;
	}
	return 1;
}

Int32 treenode_width_priority_traverse (struct tree_node *node, Int32 (*visit) (struct tree_node*)) {
	if (!node)
		return -1;

	Int32 i;
	for (i = 0; i < node->child_count; ++i) {
		if (visit(node->childs[i]) < 0)
			return -1;
	}

	for (i = 0; i < node->child_count; ++i) {
		if (treenode_width_priority_traverse(node->childs[i], visit) < 0)
			return -1;
	}
	return 1;
}

Int32 treenode_get_node_distance (struct tree_node *n1, struct tree_node *n2) {
	Int32 ret = -1;
	struct tree_node *parent = treenode_get_nearest_parent(n1,n2);
	if (!parent)
		return ret;
	int depth_parent = treenode_get_node_depth(parent);
	int depth_n1 = treenode_get_node_depth(n1);
	int depth_n2 = treenode_get_node_depth(n2);
	ret = depth_n1 - depth_parent + depth_n2 - depth_parent;
	return ret;
}

Boolean treenode_is_parent_of (struct tree_node *n1, struct tree_node *n2) {
	if (!n2)
		return false;
	struct tree_node *parent = n2->parent;
	while (parent) {
		if (treenode_equal_node(parent,n1)) {
			return true;
		}
		parent = parent->parent;
	}
	return false;
}

Boolean treenode_is_child_of (struct tree_node *n1, struct tree_node *n2) {
	return treenode_is_parent_of(n2,n1);
}

struct tree_node* treenode_get_nearest_parent (struct tree_node *n1, struct tree_node *n2) {
	if (treenode_is_parent_of(n1,n2))
		return n1;
	if (treenode_is_parent_of(n2,n1))
		return n2;

	if (!n1 || !n2)
		return NULL;

	struct tree_node *p1 = n1->parent, *p2 = n2->parent;
	while (p1) {
		while(p2) {
			if (treenode_equal_node(p1,p2))
				return p1;
			p2 = p2->parent;
		}
		p1 = p1->parent;
		p2 = n2->parent;
	}
	return NULL;
}

Int32 treenode_get_node_depth (struct tree_node *node) {
	if (!node)
		return -1;
	Int32 ret = 0;
	struct tree_node *p = node->parent;
	if (!p)
		return ret;
	while(p) {
		p = p->parent;
		++ret;
	}
	return ret;
}
