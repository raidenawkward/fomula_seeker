#include "used_set.h"

Boolean used_set_init(struct used_set **set, Int32 count) {
	if (count < 0)
        return false;
    *set = (struct used_set*)malloc(sizeof(struct used_set));
    if (!*set)
        return false;
    (*set)->used = (Boolean*)malloc(count * sizeof(Boolean));
    if (!(*set)->used)
        return false;
    (*set)->count = count;
    used_set_clear(*set);
    return true;
}

void used_set_destory(struct used_set **set) {
	if (!set)
        return;
	if (!*set)
		return;
    if ((*set)->used && (*set)->count > 0)
        free((*set)->used);
    free(*set);
}

void used_set_clear(struct used_set *set) {
	if (!set)
		return;
	if (!set->used || set->count <= 0)
        return;
    Int32 i;
    for (i = 0; i < set->count; ++i) {
        set->used[i] = false;
    }
}
