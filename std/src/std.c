/* $CORTO_GENERATED
 *
 * std.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <corto/t/std/std.h>

/* $header() */
#include "math.h"

static corto_bool corto_t_std_if_intern(
    corto_value *arg,
    corto_bool invert,
    corto_t_block* block,
    corto_word ctx)
{
    corto_bool result = FALSE;

    if (arg) {
        result = *(corto_bool*)corto_value_getPtr(arg);
        if ((!invert && result) || (invert && !result)) {
            corto_t_block_run(block, ctx);
        }
    }

    return (result + invert) % 2;
}

typedef struct corto_t_ser_t {
    corto_t_block *block;
    corto_word ctx;
    corto_uint64 n;
} corto_t_ser_t;

corto_int16 corto_t_ser_item(
    corto_serializer s,
    corto_value *info,
    void *userData)
{
    corto_t_ser_t *data = userData;

    corto_t_var v[] = {
        {"", *info},
        {"n", corto_value_literalInteger(data->n)},
        {NULL}
    };

    corto_t_frame f = {corto_t_finddefault, v};

    corto_t_pushframe(&f, data->ctx);
    corto_t_block_run(data->block, data->ctx);
    corto_t_popframe(data->ctx);

    data->n ++;

    return 0;
}

struct corto_serializer_s corto_t_ser(void) {
    struct corto_serializer_s s;
    corto_serializerInit(&s);
    s.access = CORTO_PRIVATE | CORTO_LOCAL;
    s.accessKind = CORTO_NOT;
    s.metaprogram[CORTO_MEMBER] = corto_t_ser_item;
    s.metaprogram[CORTO_ELEMENT] = corto_t_ser_item;
    return s;
}
/* $end */

corto_int64 _corto_t_std_abs(
    corto_int64 arg)
{
/* $begin(corto/t/std/abs) */

    return llabs(arg);

/* $end */
}

corto_uint64 _corto_t_std_count(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx)
{
/* $begin(corto/t/std/count) */
    corto_type t = corto_value_getType(arg);
    corto_uint64 result = 0;

    if (t->kind == CORTO_COLLECTION) {
        void *ptr = corto_value_getPtr(arg);
        switch(corto_collection(t)->kind) {
        case CORTO_ARRAY:
            result = corto_collection(t)->max;
            break;
        case CORTO_SEQUENCE:
            result = ((corto_objectseq*)ptr)->length;
            break;
        case CORTO_LIST:
            result = corto_llSize(*(corto_ll*)ptr);
            break;
        case CORTO_MAP:
            result = corto_rbtreeSize(*(corto_rbtree*)ptr);
            break;
        }
    } else if (t->kind == CORTO_COMPOSITE) {
        result = corto_interface(t)->members.length;
    }

    return result;
/* $end */
}

corto_bool _corto_t_std_declared(
    corto_value* arg1,
    corto_value* arg2,
    corto_word ctx)
{
/* $begin(corto/t/std/declared) */
    if (arg1) {
        corto_type t = corto_value_getType(arg1);
        if ((arg1->kind == CORTO_OBJECT) || t->reference) {
            return corto_checkState(corto_value_getPtr(arg1), CORTO_DECLARED);
        } else {
            return FALSE;
        }
    } else {
        return FALSE;
    }
/* $end */
}

corto_bool _corto_t_std_defined(
    corto_value* arg1,
    corto_value* arg2,
    corto_word ctx)
{
/* $begin(corto/t/std/defined) */
    if (arg1) {
        corto_type t = corto_value_getType(arg1);
        if ((arg1->kind == CORTO_OBJECT) || t->reference) {
            return corto_checkState(corto_value_getPtr(arg1), CORTO_DEFINED);
        } else {
            return FALSE;
        }
    } else {
        return FALSE;
    }
/* $end */
}

corto_void _corto_t_std_each(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx)
{
/* $begin(corto/t/std/each) */
    struct corto_serializer_s s = corto_t_ser();
    corto_t_ser_t walkData = {block, ctx, 0};

    corto_serializeValue(&s, arg, &walkData);
/* $end */
}

corto_bool _corto_t_std_elif(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx)
{
/* $begin(corto/t/std/elif) */
    corto_bool *cond = corto_value_getPtr(chainArg);

    /* Default to TRUE so that when block isn't executed, a chained function
     * that follows elif also isn't executed. */
    corto_bool result = TRUE;

    if (!*cond) {
        result = corto_t_std_if_intern(arg, FALSE, block, ctx);
    }

    return result;
/* $end */
}

corto_bool _corto_t_std_elifn(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx)
{
/* $begin(corto/t/std/elifn) */
    corto_bool *cond = corto_value_getPtr(chainArg);

    /* Default to TRUE so that when block isn't executed, a chained function
     * that follows elif also isn't executed. */
    corto_bool result = TRUE;

    if (!*cond) {
        result = corto_t_std_if_intern(arg, TRUE, block, ctx);
    }

    return result;
/* $end */
}

corto_void _corto_t_std_else(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx)
{
/* $begin(corto/t/std/else) */
    corto_bool *cond = corto_value_getPtr(chainArg);

    if (!*cond) {
        corto_t_block_run(block, ctx);
    }

/* $end */
}

corto_string _corto_t_std_id(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx)
{
/* $begin(corto/t/std/id) */
    if (arg) {
        corto_type t = corto_value_getType(arg);

        if ((arg->kind == CORTO_OBJECT) || t->reference) {
            return corto_strdup(corto_idof(corto_value_getObject(arg)));
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
/* $end */
}

corto_bool _corto_t_std_if(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx)
{
/* $begin(corto/t/std/if) */

    return corto_t_std_if_intern(arg, FALSE, block, ctx);

/* $end */
}

corto_bool _corto_t_std_ifn(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx)
{
/* $begin(corto/t/std/ifn) */

    return corto_t_std_if_intern(arg, TRUE, block, ctx);

/* $end */
}

corto_bool _corto_t_std_instanceof(
    corto_value* arg1,
    corto_value* arg2,
    corto_word ctx)
{
/* $begin(corto/t/std/instanceof) */
    if (arg1) {
        corto_type valueType = corto_value_getType(arg1);
        corto_type t = corto_value_getPtr(arg2);
        if (corto_instanceofType(t, valueType)) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        return FALSE;
    }
/* $end */
}

corto_string _corto_t_std_lower(
    corto_string arg)
{
/* $begin(corto/t/std/lower) */
    corto_string result = strdup(arg);
    corto_strupper(result);
    return result;
/* $end */
}

corto_string _corto_t_std_name(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx)
{
/* $begin(corto/t/std/name) */

    if (arg) {
        corto_type t = corto_value_getType(arg);
        void *ptr = corto_value_getPtr(arg);
        if ((arg->kind == CORTO_OBJECT) || t->reference) {
            corto_id id;
            return corto_strdup(corto_nameof(id, ptr));
        } else {
            corto_seterr("t/std/name called on value that is not an object");
            return NULL;
        }
    } else {
        return NULL;
    }
/* $end */
}

corto_bool _corto_t_std_observable(
    corto_value* arg1,
    corto_value* arg2,
    corto_word ctx)
{
/* $begin(corto/t/std/observable) */
    if (arg1) {
        corto_type t = corto_value_getType(arg1);
        if ((arg1->kind == CORTO_OBJECT) || t->reference) {
            return corto_checkAttr(corto_value_getPtr(arg1), CORTO_ATTR_OBSERVABLE);
        } else {
            return FALSE;
        }
    } else {
        return FALSE;
    }
/* $end */
}

corto_object _corto_t_std_parent(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx)
{
/* $begin(corto/t/std/parent) */
    if (arg) {
        corto_type t = corto_value_getType(arg);
        if ((arg->kind == CORTO_OBJECT) || t->reference) {
            corto_object result = corto_parentof(corto_value_getObject(arg));
            corto_claim(result); /* Return claim */
            return result;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
/* $end */
}

corto_bool _corto_t_std_persistent(
    corto_value* arg1,
    corto_value* arg2,
    corto_word ctx)
{
/* $begin(corto/t/std/persistent) */
    if (arg1) {
        corto_type t = corto_value_getType(arg1);
        if ((arg1->kind == CORTO_OBJECT) || t->reference) {
            return corto_checkAttr(corto_value_getPtr(arg1), CORTO_ATTR_PERSISTENT);
        } else {
            return FALSE;
        }
    } else {
        return FALSE;
    }

/* $end */
}

corto_float64 _corto_t_std_pow(
    corto_float64 base,
    corto_float64 exponent)
{
/* $begin(corto/t/std/pow) */
    return pow(base, exponent);
/* $end */
}

corto_string _corto_t_std_replace(
    corto_string s,
    corto_string old,
    corto_string _new)
{
/* $begin(corto/t/std/replace) */

    return corto_replace(s, old, _new);

/* $end */
}

corto_void _corto_t_std_scope(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx)
{
/* $begin(corto/t/std/scope) */

    /* << Insert implementation >> */

/* $end */
}

corto_bool _corto_t_std_scoped(
    corto_value* arg1,
    corto_value* arg2,
    corto_word ctx)
{
/* $begin(corto/t/std/scoped) */
    if (arg1) {
        corto_type t = corto_value_getType(arg1);
        if ((arg1->kind == CORTO_OBJECT) || t->reference) {
            return corto_checkAttr(corto_value_getPtr(arg1), CORTO_ATTR_SCOPED);
        } else {
            return FALSE;
        }
    } else {
        return FALSE;
    }

/* $end */
}

corto_uint64 _corto_t_std_toint(
    corto_float64 arg)
{
/* $begin(corto/t/std/toint) */

    return (corto_uint64)arg;

/* $end */
}

corto_type _corto_t_std_type(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx)
{
/* $begin(corto/t/std/type) */
    if (arg) {
        corto_type t = corto_value_getType(arg);
        if ((arg->kind == CORTO_OBJECT) || t->reference) {
            corto_object result = corto_typeof(corto_value_getObject(arg));
            corto_claim(result); /* Return claim */
            return result;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
/* $end */
}

corto_string _corto_t_std_upper(
    corto_string arg)
{
/* $begin(corto/t/std/upper) */
    corto_string result = strdup(arg);
    corto_strupper(result);
    return result;
/* $end */
}

corto_bool _corto_t_std_valid(
    corto_value* arg1,
    corto_value* arg2,
    corto_word ctx)
{
/* $begin(corto/t/std/valid) */
    if (arg1) {
        corto_type t = corto_value_getType(arg1);
        if ((arg1->kind == CORTO_OBJECT) || t->reference) {
            return corto_checkState(corto_value_getPtr(arg1), CORTO_VALID);
        } else {
            return FALSE;
        }
    } else {
        return FALSE;
    }

/* $end */
}

int stdMain(int argc, char *argv[]) {
/* $begin(main) */

    /* Insert code that must be run when component is loaded */

    return 0;
/* $end */
}
