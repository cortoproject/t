/* $CORTO_GENERATED
 *
 * function.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <corto/t/t.h>

corto_int16 _corto_t_function_init(
    corto_t_function this)
{
/* $begin(corto/t/function/init) */

    corto_parameterSet(
        corto_parameterseqAppendAlloc(&corto_function(this)->parameters),
        "arg",
        corto_t_value_o,
        FALSE
    );

    corto_parameterSet(
        corto_parameterseqAppendAlloc(&corto_function(this)->parameters),
        "block",
        corto_t_block_o,
        FALSE
    );

    corto_parameterSet(
        corto_parameterseqAppendAlloc(&corto_function(this)->parameters),
        "context",
        corto_t_context_o,
        FALSE
    );

    return corto_function_init(this);
/* $end */
}