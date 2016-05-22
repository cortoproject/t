/* $CORTO_GENERATED
 *
 * comparator.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <corto/t/t.h>

corto_int16 _corto_t_comparator_init(
    corto_t_comparator this)
{
/* $begin(corto/t/comparator/init) */

    corto_parameterSet(
        corto_parameterseqAppendAlloc(&corto_function(this)->parameters),
        "arg1",
        corto_t_value_o,
        FALSE
    );

    corto_parameterSet(
        corto_parameterseqAppendAlloc(&corto_function(this)->parameters),
        "arg2",
        corto_t_value_o,
        FALSE
    );

    corto_setref(&corto_function(this)->returnType, corto_bool_o);

    return corto_function_init(this);
/* $end */
}
