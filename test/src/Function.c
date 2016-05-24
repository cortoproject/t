/* $CORTO_GENERATED
 *
 * Function.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <test.h>

corto_void _test_Function_tc_function(
    test_Function this)
{
/* $begin(test/Function/tc_function) */
    corto_int32CreateChild_auto(root_o, i, 10);

    corto_t_var vars[] = {
        {"var", corto_value_object(i, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${name var}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "i");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Function_tc_functionCastStrToBool1(
    test_Function this)
{
/* $begin(test/Function/tc_functionCastStrToBool1) */
    corto_stringCreateChild_auto(root_o, i, "true");

    corto_t_var vars[] = {
        {"var", corto_value_object(i, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${if var}Hello World!${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Hello World!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Function_tc_functionCastStrToBool2(
    test_Function this)
{
/* $begin(test/Function/tc_functionCastStrToBool2) */
    corto_stringCreateChild_auto(root_o, i, "false");

    corto_t_var vars[] = {
        {"var", corto_value_object(i, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${if var}Hello World!${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Function_tc_functionEmbed(
    test_Function this)
{
/* $begin(test/Function/tc_functionEmbed) */
    corto_int32CreateChild_auto(root_o, world, 10);

    corto_t_var vars[] = {
        {"var", corto_value_object(world, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("Hello ${name var}!");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Hello world!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Function_tc_functionMultiple(
    test_Function this)
{
/* $begin(test/Function/tc_functionMultiple) */
    corto_int32CreateChild_auto(root_o, wonderful, 10);
    corto_int32CreateChild_auto(root_o, world, 10);

    corto_t_var vars[] = {
        {"var1", corto_value_object(wonderful, NULL)},
        {"var2", corto_value_object(world, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("Hello ${name var1} ${name var2}!");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Hello wonderful world!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Function_tc_functionNotExist(
    test_Function this)
{
/* $begin(test/Function/tc_functionNotExist) */

    corto_t *t = corto_t_compile("Hello ${foo var}!");
    test_assert(t == NULL);
    test_assert(corto_lasterr() != NULL);
    test_assertstr(corto_lasterr(), "unknown function near 'foo var}!'");

/* $end */
}

corto_void _test_Function_tc_functionObject(
    test_Function this)
{
/* $begin(test/Function/tc_functionObject) */
    corto_int32CreateChild_auto(root_o, i, 10);

    corto_t_frame ctx = {NULL, NULL};

    /* Compile template */
    corto_t *t = corto_t_compile("${name /i}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "i");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Function_tc_functionTwice(
    test_Function this)
{
/* $begin(test/Function/tc_functionTwice) */
    corto_int32CreateChild_auto(root_o, world, 10);

    corto_t_var vars[] = {
        {"var", corto_value_object(world, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("Hello ${name var} ${name var}!");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Hello world world!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Function_tc_functionVoid(
    test_Function this)
{
/* $begin(test/Function/tc_functionVoid) */
    corto_bool v_false = FALSE;
    corto_t_var vars[] = {
        {"f", corto_value_value(corto_bool_o, &v_false)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${if f}Yes!${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Function_tc_functionWhitespace1(
    test_Function this)
{
/* $begin(test/Function/tc_functionWhitespace1) */
    corto_int32CreateChild_auto(root_o, i, 10);

    corto_t_var vars[] = {
        {"var", corto_value_object(i, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${  name var}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "i");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Function_tc_functionWhitespace2(
    test_Function this)
{
/* $begin(test/Function/tc_functionWhitespace2) */
    corto_int32CreateChild_auto(root_o, i, 10);

    corto_t_var vars[] = {
        {"var", corto_value_object(i, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${name var  }");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "i");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Function_tc_functionWhitespace3(
    test_Function this)
{
/* $begin(test/Function/tc_functionWhitespace3) */
    corto_int32CreateChild_auto(root_o, i, 10);

    corto_t_var vars[] = {
        {"var", corto_value_object(i, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${  name var  }");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "i");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}
