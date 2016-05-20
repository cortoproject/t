/* $CORTO_GENERATED
 *
 * Chain.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <test.h>

corto_void _test_Chain_tc_chainFalse(
    test_Chain this)
{
/* $begin(test/Chain/tc_chainFalse) */
    corto_bool v_false = FALSE;
    corto_t_var vars[] = {
        {"f", corto_value_value(corto_bool_o, &v_false)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${if f}Yes!${else}No!${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "No!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Chain_tc_chainThreeFF(
    test_Chain this)
{
/* $begin(test/Chain/tc_chainThreeFF) */
    corto_bool v_true = TRUE, v_false = FALSE;
    corto_t_var vars[] = {
        {"t", corto_value_value(corto_bool_o, &v_true)},
        {"f", corto_value_value(corto_bool_o, &v_false)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${if f}Yes!${elif f}Maybe!${else}No!${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "No!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Chain_tc_chainThreeFT(
    test_Chain this)
{
/* $begin(test/Chain/tc_chainThreeFT) */
    corto_bool v_true = TRUE, v_false = FALSE;
    corto_t_var vars[] = {
        {"t", corto_value_value(corto_bool_o, &v_true)},
        {"f", corto_value_value(corto_bool_o, &v_false)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${if f}Yes!${elif t}Maybe!${else}No!${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Maybe!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Chain_tc_chainThreeTF(
    test_Chain this)
{
/* $begin(test/Chain/tc_chainThreeTF) */
    corto_bool v_true = TRUE, v_false = FALSE;
    corto_t_var vars[] = {
        {"t", corto_value_value(corto_bool_o, &v_true)},
        {"f", corto_value_value(corto_bool_o, &v_false)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${if t}Yes!${elif f}Maybe!${else}No!${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Yes!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Chain_tc_chainThreeTT(
    test_Chain this)
{
/* $begin(test/Chain/tc_chainThreeTT) */
    corto_bool v_true = TRUE, v_false = FALSE;
    corto_t_var vars[] = {
        {"t", corto_value_value(corto_bool_o, &v_true)},
        {"f", corto_value_value(corto_bool_o, &v_false)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${if t}Yes!${elif t}Maybe!${else}No!${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Yes!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Chain_tc_chainTrue(
    test_Chain this)
{
/* $begin(test/Chain/tc_chainTrue) */
    corto_bool v_true = TRUE;
    corto_t_var vars[] = {
        {"t", corto_value_value(corto_bool_o, &v_true)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${if t}Yes!${else}No!${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Yes!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}
