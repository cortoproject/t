/* $CORTO_GENERATED
 *
 * Comparator.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/test.h>

corto_void _test_Comparator_tc_comparator2ArgFalse(
    test_Comparator this)
{
/* $begin(test/Comparator/tc_comparator2ArgFalse) */
    corto_int32CreateChild_auto(root_o, i, 10);

    corto_t_var vars[] = {
        {"var", corto_value_object(i, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${if var is instanceof float32}Floating Point!${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Comparator_tc_comparator2ArgTrue(
    test_Comparator this)
{
/* $begin(test/Comparator/tc_comparator2ArgTrue) */
    corto_int32CreateChild_auto(root_o, i, 10);

    corto_t_var vars[] = {
        {"var", corto_value_object(i, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${if var is instanceof int32}Integer!${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Integer!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Comparator_tc_comparatorFalse(
    test_Comparator this)
{
/* $begin(test/Comparator/tc_comparatorFalse) */
    corto_int32Create_auto(i, 10);

    corto_t_var vars[] = {
        {"var", corto_value_object(i, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${if var is scoped}Scoped!${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Comparator_tc_comparatorTrue(
    test_Comparator this)
{
/* $begin(test/Comparator/tc_comparatorTrue) */
    corto_int32CreateChild_auto(root_o, i, 10);

    corto_t_var vars[] = {
        {"var", corto_value_object(i, NULL)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${if var is scoped}Scoped!${end}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Scoped!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}
