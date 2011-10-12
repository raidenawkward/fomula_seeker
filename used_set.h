#ifndef _USED_SET_H
#define _USED_SET_H

#include <stdlib.h>
#include "tree_define.h"

struct used_set {
    Boolean *used;
    Int32 count;
};

Boolean used_set_init(struct used_set **set, Int32 count);
void used_set_destory(struct used_set **set);
void used_set_clear(struct used_set *set);

Int32 used_set_used_num(struct used_set *set);
Int32 used_set_unused_num(struct used_set *set);
/// union s1 and s2 to s1, count of s1 and s2 must be same
Boolean used_set_union(struct used_set *s1, struct used_set *s2);
// if current_index equals -1, finds first used or unused index
Int32 used_set_next_used_index(struct used_set *set, Int32 current_index);
Int32 used_set_next_unused_index(struct used_set *set, Int32 current_index);

#endif //_USED_SET_H
