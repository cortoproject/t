/* $CORTO_GENERATED
 *
 * DefaultVar.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <test.h>

corto_void _test_DefaultVar_tc_default(
    test_DefaultVar this)
{
/* $begin(test/DefaultVar/tc_default) */
    test_Point v = {10, 20};
    corto_t_var vars[] = {
        {"var", corto_value_value(test_Point_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${each var}$ ${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "10 20 ");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_DefaultVar_tc_defaultBraces(
    test_DefaultVar this)
{
/* $begin(test/DefaultVar/tc_defaultBraces) */
    test_Point v = {10, 20};
    corto_t_var vars[] = {
        {"var", corto_value_value(test_Point_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${each var}${.} ${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "10 20 ");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_DefaultVar_tc_defaultDot(
    test_DefaultVar this)
{
/* $begin(test/DefaultVar/tc_defaultDot) */
    test_Point v = {10, 20};
    corto_t_var vars[] = {
        {"var", corto_value_value(test_Point_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${each var}$. ${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "10 20 ");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}
