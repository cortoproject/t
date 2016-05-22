/* $CORTO_GENERATED
 *
 * std.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <corto/t/std/std.h>

/* $header() */
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
} corto_t_ser_t;

corto_int16 corto_t_ser_item(
    corto_serializer s,
    corto_value *info,
    void *userData)
{
    corto_t_ser_t *data = userData;
    corto_t_var v = {"", *info};

    corto_t_frame f = {corto_t_finddefault, &v};

    corto_t_pushframe(&f, data->ctx);
    corto_t_block_run(data->block, data->ctx);
    corto_t_popframe(data->ctx);

    return 0;
}

struct corto_serializer_s corto_t_ser() {
    struct corto_serializer_s s;
    corto_serializerInit(&s);
    s.access = CORTO_PRIVATE | CORTO_LOCAL;
    s.accessKind = CORTO_NOT;
    s.metaprogram[CORTO_MEMBER] = corto_t_ser_item;
    s.metaprogram[CORTO_ELEMENT] = corto_t_ser_item;
    return s;
}
/* $end */

corto_void _corto_t_std_each(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx)
{
/* $begin(corto/t/std/each) */
    struct corto_serializer_s s = corto_t_ser();
    corto_t_ser_t walkData = {block, ctx};

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

int stdMain(int argc, char* argv[]) {
/* $begin(main) */

    /* Insert code that must be run when component is loaded */

    return 0;
/* $end */
}
