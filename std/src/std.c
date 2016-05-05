/* $CORTO_GENERATED
 *
 * std.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <corto/t/std/std.h>

corto_void _corto_t_std_else(
    corto_string arg,
    corto_t_block* block,
    corto_word ctx)
{
/* $begin(corto/t/std/else) */

    /* << Insert implementation >> */

/* $end */
}

corto_void _corto_t_std_foreach(
    corto_string arg,
    corto_t_block* block,
    corto_word ctx)
{
/* $begin(corto/t/std/foreach) */

    /* << Insert implementation >> */

/* $end */
}

corto_string _corto_t_std_id(
    corto_string arg,
    corto_t_block* block,
    corto_word ctx)
{
/* $begin(corto/t/std/id) */

    /* << Insert implementation >> */

/* $end */
}

corto_void _corto_t_std_if(
    corto_string arg,
    corto_t_block* block,
    corto_word ctx)
{
/* $begin(corto/t/std/if) */
    corto_t_var *var = corto_t_findvar(arg, ctx);
    corto_bool result = FALSE;

    if (var) {
        corto_type t = corto_value_getType(&var->value);
        void *ptr = corto_value_getPtr(&var->value);

        if (corto_instanceof(corto_boolean_o, t)) {
            result = *(corto_bool*)ptr;
        } else if (var->value.kind == CORTO_OBJECT) {
            result = ptr != NULL;
        } else if (t->reference) {
            result = *(corto_object*)ptr != NULL;
        } else if (t->kind == CORTO_PRIMITIVE) {
            corto_convert(t, ptr, corto_bool_o, &result);
        } else {
            /* Cannot reduce value to boolean */
            corto_seterr("cannot convert value of type '%s' to boolean",
                corto_fullpath(NULL, t));
        }
    } else {
        /* If variable doesn't exist, assume FALSE */
    }

    if (result) {
        corto_t_block_run(block, ctx);
    }

/* $end */
}

corto_string _corto_t_std_name(
    corto_string arg,
    corto_t_block* block,
    corto_word ctx)
{
/* $begin(corto/t/std/name) */
    corto_t_var *var = corto_t_findvar(arg, ctx);

    if (var) {
        corto_type t = corto_value_getType(&var->value);
        void *ptr = corto_value_getPtr(&var->value);
        if ((var->value.kind == CORTO_OBJECT) || t->reference) {
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
    corto_string arg,
    corto_t_block* block,
    corto_word ctx)
{
/* $begin(corto/t/std/parent) */

    /* << Insert implementation >> */

/* $end */
}

corto_void _corto_t_std_scope(
    corto_string arg,
    corto_t_block* block,
    corto_word ctx)
{
/* $begin(corto/t/std/scope) */

    /* << Insert implementation >> */

/* $end */
}

corto_type _corto_t_std_type(
    corto_string arg,
    corto_t_block* block,
    corto_word ctx)
{
/* $begin(corto/t/std/type) */

    /* << Insert implementation >> */

/* $end */
}

int stdMain(int argc, char* argv[]) {
/* $begin(main) */

    /* Insert code that must be run when component is loaded */

    return 0;
/* $end */
}
