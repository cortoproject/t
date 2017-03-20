/* $CORTO_GENERATED
 *
 * Literals.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/test.h>

corto_void _test_Literals_tc_false(
    test_Literals this)
{
/* $begin(test/Literals/tc_false) */

    /* Compile template */
    corto_t *t = corto_t_compile("${false}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, NULL);
    test_assert(str != NULL);
    test_assertstr(str, "false");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Literals_tc_number(
    test_Literals this)
{
/* $begin(test/Literals/tc_number) */

    /* Compile template */
    corto_t *t = corto_t_compile("${10}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, NULL);
    test_assert(str != NULL);
    test_assertstr(str, "10.000000");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Literals_tc_numberFloat(
    test_Literals this)
{
/* $begin(test/Literals/tc_numberFloat) */

    /* Compile template */
    corto_t *t = corto_t_compile("${10.5}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, NULL);
    test_assert(str != NULL);
    test_assertstr(str, "10.500000");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Literals_tc_numberNegative(
    test_Literals this)
{
/* $begin(test/Literals/tc_numberNegative) */

    /* Compile template */
    corto_t *t = corto_t_compile("${-10}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, NULL);
    test_assert(str != NULL);
    test_assertstr(str, "-10.000000");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Literals_tc_string(
    test_Literals this)
{
/* $begin(test/Literals/tc_string) */

    /* Compile template */
    corto_t *t = corto_t_compile("${\"Hello World\"}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, NULL);
    test_assert(str != NULL);
    test_assertstr(str, "Hello World");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Literals_tc_true(
    test_Literals this)
{
/* $begin(test/Literals/tc_true) */

    /* Compile template */
    corto_t *t = corto_t_compile("${true}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, NULL);
    test_assert(str != NULL);
    test_assertstr(str, "true");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}
