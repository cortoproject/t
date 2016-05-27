/* $CORTO_GENERATED
 *
 * Filter.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <test.h>

corto_void _test_Filter_tc_filterFunc(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterFunc) */
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

corto_void _test_Filter_tc_filterVar(
    test_Filter this)
{
/* $begin(test/Filter/tc_filterVar) */
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
