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

Int32 used_set_used_num(struct used_set *set) {
	if (!set)
		return 0;

	Int32 i,ret = 0;
	for (i = 0; i < set->count; ++i) {
		if (set->used[i])
			++ret;
	}
	return ret;
}

Int32 used_set_unused_num(struct used_set *set) {
	if (!set)
		return 0;
	return set->count - used_set_used_num(set);
}

Boolean used_set_union(struct used_set *s1, struct used_set *s2) {
	if (!s1 || !s2)
		return false;
	if (s1->count != s2->count || !s1->used)
		return false;

	if (!s2->used)
		return true;

	Int32 i;
	for (i = 0; i < s1->count; ++i) {
		s1->used[i] = s1->used[i] || s2->used[i];
	}

	return true;
}

Int32 used_set_next_used_index(struct used_set *set, Int32 current_index) {
	if (!set || current_index < 0)
		return -1;
	Int32 i = current_index + 1;
	for (; i < set->count; ++i) {
		if (set->used[i])
			return i;
	}
	return -1;
}

Int32 used_set_next_unused_index(struct used_set *set, Int32 current_index) {
	if (!set || current_index < 0)
		return -1;
	Int32 i = current_index + 1;
	for (; i < set->count; ++i) {
		if (!set->used[i])
			return i;
	}
	return -1;

}
