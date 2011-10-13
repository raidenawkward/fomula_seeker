#ifndef _FOMULA_PARSE_H
#define _FOMULA_PARSE_H

#include <stdlib.h>
#include "fomula_seek_define.h"
#include "tree_define.h"
#include "tree_node.h"

#define FOMULA_SYMBOL_OPERATOR_PLUS "+"
#define FOMULA_SYMBOL_OPERATOR_SUBSRACT "-"
#define FOMULA_SYMBOL_OPERATOR_MULTIPLE "*"
#define FOMULA_SYMBOL_OPERATOR_DIVISION "/"

Boolean tree_branch_calculated_result(struct tree_node *branch_header, Int32 *result);
Boolean tree_branch_fomula_string(struct tree_node *branch_header, Char** result);

#endif // _FOMULA_PARSE_H
