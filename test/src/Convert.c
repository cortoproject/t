/* $CORTO_GENERATED
 *
 * Convert.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/test.h>

corto_void _test_Convert_tc_convertBooleanVar(
    test_Convert this)
{
/* $begin(test/Convert/tc_convertBooleanVar) */
    corto_bool v = TRUE;
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_bool_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("$var");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "true");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Convert_tc_convertCollectionVar(
    test_Convert this)
{
/* $begin(test/Convert/tc_convertCollectionVar) */
    test_Point v[] = {{10, 20}, {30, 40}, {50, 60}};
    corto_t_var vars[] = {
        {"var", corto_value_value(test_Points_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("$var");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "{{10,20},{30,40},{50,60}}");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Convert_tc_convertCompositeVar(
    test_Convert this)
{
/* $begin(test/Convert/tc_convertCompositeVar) */
    test_Point v = {10, 20};
    corto_t_var vars[] = {
        {"var", corto_value_value(test_Point_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("$var");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "{10,20}");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Convert_tc_convertNumericVar(
    test_Convert this)
{
/* $begin(test/Convert/tc_convertNumericVar) */
    corto_int32 v = 10;
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_int32_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("$var");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "10");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}
