#include "base_type.h"

namespace JsonStructs {
    json_array *base_to_array(const base_type *bt) {
        if (bt->type == ETE_ARRAY) {
            json_array ja = *((json_array *) bt);
            return new json_array{ja};
        }
        return nullptr;
    }

    json_double *base_to_double(const base_type *bt) {
        if (bt->type == ETE_DOUBLE) {
            json_double jd = *((json_double *) bt);
            return new json_double{jd};
        }
        return nullptr;
    }

    json_int *base_to_int(const base_type *bt) {
        if (bt->type == ETE_INT) {
            json_int ji = *((json_int *) bt);
            return new json_int{ji};
        }
        return nullptr;
    }

    json_string *base_to_string(const base_type *bt) {
        if (bt->type == ETE_STRING) {
            json_string js = *((json_string *) bt);
            return new json_string(js);
        }
        return nullptr;
    }

    json_tree *base_to_tree(const base_type *bt) {
        if (bt->type == ETE_TREE) {
            json_tree jt = *((json_tree *) bt);
            return new json_tree(jt);
        }
        return nullptr;
    }

    base_type *base_type::get_data(const int &i) const {
        if (type == ETE_ARRAY) {
            return (*((json_array *) this))[i];
        }
        return nullptr;
    }

    void base_type::set_type(ETypeElement ntype) {
        type = ntype;
    }

    base_type *base_type::operator[](const int &i) const {
        return get_data(i);
    }
}