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

#endif //_USED_SET_H
