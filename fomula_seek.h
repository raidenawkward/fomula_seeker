#ifndef _FOMULA_SEEKER_H
#define _FOMULA_SEEKER_H

#include <stdlib.h>
#include <stdio.h>

#include "tree_define.h" // tree struct used

/// if operators which consist fomulas could be used more than once
#undef FORMULA_SEEKER_DEF_OPERATOR_USED_ONCE

/// get fomulas whose calculated result equals target, returns count of solutions, -1 if invalid params
Int32 seek_fomula(Int32 target, Int32 *num, Int32 num_count, Char ***result);

#endif // _FOMULA_SEEKER_H
