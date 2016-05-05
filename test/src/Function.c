/* $CORTO_GENERATED
 *
 * Function.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <test.h>

/* $header() */
static corto_t_var* findvar(corto_string key, void *data) {
    corto_t_var *result = NULL;
    corto_t_var *vars = data;

    for (result = vars; result->key; result ++) {
        if (!strcmp(result->key, key)) {
            break;
        }
    }

    return result->key ? result : NULL;
}
/* $end */

corto_void _test_Function_tc_function(
    test_Function this)
{
/* $begin(test/Function/tc_function) */
    corto_int32CreateChild_auto(root_o, i, 10);

    corto_t_var vars[] = {
        {"var", corto_value_object(i, NULL)},
        {NULL}
    };

    corto_t_context ctx = {findvar, vars};

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

corto_void _test_Function_tc_functionEmbed(
    test_Function this)
{
/* $begin(test/Function/tc_functionEmbed) */
    corto_int32CreateChild_auto(root_o, world, 10);

    corto_t_var vars[] = {
        {"var", corto_value_object(world, NULL)},
        {NULL}
    };

    corto_t_context ctx = {findvar, vars};

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

    corto_t_context ctx = {findvar, vars};

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

corto_void _test_Function_tc_functionTwice(
    test_Function this)
{
/* $begin(test/Function/tc_functionTwice) */
    corto_int32CreateChild_auto(root_o, world, 10);

    corto_t_var vars[] = {
        {"var", corto_value_object(world, NULL)},
        {NULL}
    };

    corto_t_context ctx = {findvar, vars};

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

corto_void _test_Function_tc_functionWhitespace1(
    test_Function this)
{
/* $begin(test/Function/tc_functionWhitespace1) */
    corto_int32CreateChild_auto(root_o, i, 10);

    corto_t_var vars[] = {
        {"var", corto_value_object(i, NULL)},
        {NULL}
    };

    corto_t_context ctx = {findvar, vars};

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

    corto_t_context ctx = {findvar, vars};

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

    corto_t_context ctx = {findvar, vars};

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
