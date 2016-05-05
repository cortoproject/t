/* $CORTO_GENERATED
 *
 * Block.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <test.h>

corto_void _test_Block_tc_block(
    test_Block this)
{
/* $begin(test/Block/tc_block) */
    corto_bool v_true = TRUE, v_false = FALSE;
    corto_t_var vars[] = {
        {"t", corto_value_value(corto_bool_o, &v_true)},
        {"f", corto_value_value(corto_bool_o, &v_false)},
        {NULL}
    };

    corto_t_context ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("true: ${if t}Yes!${end} false:${if f}No!${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "true: Yes! false:");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Block_tc_blockNested1(
    test_Block this)
{
/* $begin(test/Block/tc_blockNested1) */
    corto_bool v_true = TRUE, v_false = FALSE;
    corto_t_var vars[] = {
        {"t", corto_value_value(corto_bool_o, &v_true)},
        {"f", corto_value_value(corto_bool_o, &v_false)},
        {NULL}
    };

    corto_t_context ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("true: ${if t}Yes! false:${if f}No!${end}${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "true: Yes! false:");

    corto_dealloc(str);
    corto_t_free(t);
/* $end */
}

corto_void _test_Block_tc_blockNested2(
    test_Block this)
{
/* $begin(test/Block/tc_blockNested2) */
    corto_bool v_true = TRUE, v_false = FALSE;
    corto_t_var vars[] = {
        {"t", corto_value_value(corto_bool_o, &v_true)},
        {"f", corto_value_value(corto_bool_o, &v_false)},
        {NULL}
    };

    corto_t_context ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("false: ${if f}No! true:${if t}Yes!${end}${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "false: ");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}
