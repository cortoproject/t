/* $CORTO_GENERATED
 *
 * Filter.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <test.h>

corto_void _test_Filter_tc_filterFunction(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterFunction) */
    corto_int32CreateChild_auto(root_o, i, 10);

    corto_t_var vars[] = {
        {"var", corto_value_object(i, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${name var | upper}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "I");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Filter_tc_filterFunctionNum(
    test_Filter this)
{
/* $begin(test/Identifier/tc_identifierMember) */
    test_Point p = {10, 20};
    corto_t_var vars[] = {
        {"var", corto_value_value(test_Point_o, &p)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${count var | abs}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "2");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Filter_tc_filterLiteral(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterLiteral) */
    /* Compile template */
    corto_t *t = corto_t_compile("${\"hello world\" | upper}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, NULL);
    test_assert(str != NULL);
    test_assertstr(str, "HELLO WORLD");

    corto_dealloc(str);
    corto_t_free(t);
/* $end */
}

corto_void _test_Filter_tc_filterLiteralNum(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterLiteralNum) */

    /* Compile template */
    corto_t *t = corto_t_compile("${-10 | abs}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, NULL);
    test_assert(str != NULL);
    test_assertstr(str, "10");

    corto_dealloc(str);
    corto_t_free(t);
/* $end */
}

corto_void _test_Filter_tc_filterVariable(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterVariable) */
    corto_string v_str = "foo";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v_str)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${var | upper}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "FOO");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Filter_tc_filterVariableNum(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterVariableNum) */
    corto_int64 v_num = -10;
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_int64_o, &v_num)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${var | abs}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "10");

    corto_dealloc(str);
    corto_t_free(t);
/* $end */
}
