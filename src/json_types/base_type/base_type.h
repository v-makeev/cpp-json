#pragma once
#include "../../structs.h"

namespace JsonStructs {
    json_array *base_to_array(const base_type *bt);
    json_double *base_to_double(const base_type *bt);
    json_int *base_to_int(const base_type *bt);
    json_string *base_to_string(const base_type *bt);
    json_tree *base_to_tree(const base_type *bt);
};