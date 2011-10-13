#include "fomula_parse.h"
#include <string.h>


static Char* operator_to_str(SeekerOperator operator) {
	Char* ret = NULL;
	Int32 length = 0;

	switch (operator) {
	case OPERA_PLUS:
		length = strlen(FOMULA_SYMBOL_OPERATOR_PLUS);
		ret = (Char*)malloc(length * sizeof(Char));
		strcpy(ret,FOMULA_SYMBOL_OPERATOR_PLUS);
		break;
	case OPERA_SUBTRACT:
		length = strlen(FOMULA_SYMBOL_OPERATOR_SUBSRACT);
		ret = (Char*)malloc(length * sizeof(Char));
		strcpy(ret,FOMULA_SYMBOL_OPERATOR_SUBSRACT);
		break;
	case OPERA_MULTIPLE:
		length = strlen(FOMULA_SYMBOL_OPERATOR_MULTIPLE);
		ret = (Char*)malloc(length * sizeof(Char));
		strcpy(ret,FOMULA_SYMBOL_OPERATOR_MULTIPLE);
		break;
	case OPERA_DIVIDE:
		length = strlen(FOMULA_SYMBOL_OPERATOR_DIVISION);
		ret = (Char*)malloc(length * sizeof(Char));
		strcpy(ret,FOMULA_SYMBOL_OPERATOR_DIVISION);
		break;
	case OPERA_INVALID:
	default:
		break;
	}
	return ret;
}

static Char* num_to_str(Int32 num) {
	Char* ret;
	Int32 length = 0;
	Int32 i = num;

	do {
	++length;
	i /= 10;
	} while(i && i / 10 >= 0);
	++length;

	ret = (Char*)malloc(length * sizeof(Char));
	ret[length - 1] = '\0';
	sprintf(ret,"%d",num);
	return ret;
}

static Char* node_data_to_str(struct tree_node *node) {
	if (!node)
		return NULL;

	Char *ret = NULL;
	switch(node->flag) {
	case TNODE_TYPE_NUM:
		ret = num_to_str(node->data.data);
		break;
	case TNODE_TYPE_OPERATOR:
		ret = operator_to_str(node->data.data);
		break;
	case TNODE_TYPE_ROOT:
	case TNODE_TYPE_UNKNOWN:
	default:
		break;
	}

	return ret;
}

Boolean tree_branch_calculated_result(struct tree_node *branch_header, Int32 *result) {

}

Boolean tree_branch_fomula_string(struct tree_node *branch_header, Char **result) {
	if (!branch_header)
		return false;

	struct tree_node* current_node = branch_header;
	Int32 result_length = 0;
	while(current_node) {
		Char *node_str = node_data_to_str(current_node);
		if (node_str) {
			Int32 length = strlen(node_str);
			if (result_length == 0) {
				*result = (Char*)malloc(length * sizeof(Char));
				if (!*result)
					return false;
				strcpy(*result,node_str);
			} else {
				Char *new_ptr = (Char*)realloc(*result,(result_length + length) * sizeof(Char));
				if (new_ptr) {
					*result = new_ptr;
					strcat(*result,node_str);
				}
			}
			result_length = strlen(*result);
			free(node_str);
		}

		current_node = current_node->parent;
	}
	return true;
}
