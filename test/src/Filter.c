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
/* $begin(test/Filter/tc_filterFunctionNum) */
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

corto_void _test_Filter_tc_filterFunctionNumChain(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterFunctionNumChain) */
    test_Point p = {10, 20};
    corto_t_var vars[] = {
        {"var", corto_value_value(test_Point_o, &p)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${count var | pow(2) | toint}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "4");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Filter_tc_filterFunctionOneArg(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterFunctionOneArg) */
    test_Point p = {10, 20};
    corto_t_var vars[] = {
        {"var", corto_value_value(test_Point_o, &p)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${count var | pow(2)}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "4.000000");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Filter_tc_filterFunctionTwoArgs(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterFunctionTwoArgs) */
    corto_stringCreateChild_auto(root_o, HelloWorld, "foo");

    corto_t_var vars[] = {
        {"var", corto_value_object(HelloWorld, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${name var | replace(\"Hello\", \"Goodbye\")}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "GoodbyeWorld");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Filter_tc_filterFunctionTwoArgsDefault(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterFunctionTwoArgsDefault) */
    corto_stringCreateChild_auto(root_o, HelloWorld, "foo");

    corto_t_var vars[] = {
        {"var", corto_value_object(HelloWorld, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${name var | replace(\"Hello\")}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "World");

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

corto_void _test_Filter_tc_filterLiteralNumChain(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterLiteralNumChain) */

    /* Compile template */
    corto_t *t = corto_t_compile("${10 | pow(2) | toint}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, NULL);
    test_assert(str != NULL);
    test_assertstr(str, "100");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Filter_tc_filterLiteralOneArg(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterLiteralOneArg) */

    /* Compile template */
    corto_t *t = corto_t_compile("${2 | pow(2)}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, NULL);
    test_assert(str != NULL);
    test_assertstr(str, "4.000000");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Filter_tc_filterLiteralTwoArgs(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterLiteralTwoArgs) */

    /* Compile template */
    corto_t *t = corto_t_compile("${\"Hello World\" | replace(\"Hello\", \"Goodbye\")}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, NULL);
    test_assert(str != NULL);
    test_assertstr(str, "Goodbye World");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Filter_tc_filterLiteralTwoArgsDefault(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterLiteralTwoArgsDefault) */

    /* Compile template */
    corto_t *t = corto_t_compile("${\"Hello World\" | replace(\"Hello\")}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, NULL);
    test_assert(str != NULL);
    test_assertstr(str, " World");

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

corto_void _test_Filter_tc_filterVariableNumChain(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterVariableNumChain) */
    corto_int64 v_num = -10;
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_int64_o, &v_num)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${var | pow(2) | toint}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "100");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Filter_tc_filterVariableOneArg(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterVariableOneArg) */
    corto_int64 v_num = -10;
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_int64_o, &v_num)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${var | pow(2)}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "100.000000");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Filter_tc_filterVariableTwoArgs(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterVariableTwoArgs) */
    corto_string v_str = "Hello World";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v_str)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${var | replace(\"Hello\", \"Goodbye\")}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Goodbye World");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Filter_tc_filterVariableTwoArgsDefault(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterVariableTwoArgsDefault) */
    corto_string v_str = "Hello World";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v_str)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${var | replace(\"Hello\")}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, " World");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}
