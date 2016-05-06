/* $CORTO_GENERATED
 *
 * Identifier.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <test.h>

corto_void _test_Identifier_tc_identifier(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifier) */
    corto_string v = "world";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("$var");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "world");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierBraces(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierBraces) */
    corto_string v = "world";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v)},
        {NULL}
    };
    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${var}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "world");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierBracesEmbed(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierBracesEmbed) */
    corto_string v = "world";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("Hello $var!");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Hello world!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierBracesEmbedNotExist(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierBracesEmbedNotExist) */
    corto_string v = "world";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("Hello ${foo}!");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Hello !");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierBracesInvalid(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierBracesInvalid) */

    /* Compile template */
    corto_t *t = corto_t_compile("Hello ${*}!");
    test_assert(t == NULL);
    test_assert(corto_lasterr() != NULL);
    test_assertstr(corto_lasterr(), "invalid identifier near '*}!'");

/* $end */
}

corto_void _test_Identifier_tc_identifierBracesMultiple(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierBracesMultiple) */
    corto_string v1 = "wonderful", v2 = "world";
    corto_t_var vars[] = {
        {"var1", corto_value_value(corto_string_o, &v1)},
        {"var2", corto_value_value(corto_string_o, &v2)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("Hello ${var1} ${var2}!");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Hello wonderful world!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierBracesNotExist(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierBracesNotExist) */
    corto_string v = "world";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${foo}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierBracesTwice(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierBracesTwice) */
    corto_string v = "world";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("Hello ${var} ${var}!");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Hello world world!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierBracesWhitespace1(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierBracesWhitespace1) */
    corto_string v = "world";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${  var}");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "world");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierBracesWhitespace2(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierBracesWhitespace2) */
    corto_string v = "world";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${var  }");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "world");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierBracesWhitespace3(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierBracesWhitespace3) */
    corto_string v = "world";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("${  var  }");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "world");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierEmbed(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierEmbed) */
    corto_string v = "world";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("Hello $var!");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Hello world!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierEmbedNotExist(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierEmbedNotExist) */
    corto_string v = "world";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("Hello $foo!");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Hello !");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierEscape(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierEscape) */
    corto_string v = "world";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("Hello \\$var!");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Hello $var!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierEscapeEscape(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierEscapeEscape) */
    corto_string v = "world";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("Hello \\\\$var!");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Hello \\world!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierInvalid(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierInvalid) */

    /* Compile template */
    corto_t *t = corto_t_compile("Hello $*!");
    test_assert(t == NULL);
    test_assert(corto_lasterr() != NULL);
    test_assertstr(corto_lasterr(), "invalid identifier near '*!'");

/* $end */
}

corto_void _test_Identifier_tc_identifierMultiple(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierMultiple) */
    corto_string v1 = "wonderful", v2 = "world";
    corto_t_var vars[] = {
        {"var1", corto_value_value(corto_string_o, &v1)},
        {"var2", corto_value_value(corto_string_o, &v2)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("Hello $var1 $var2!");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Hello wonderful world!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierNotExist(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierNotExist) */
    corto_string v = "world";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("$foo");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}

corto_void _test_Identifier_tc_identifierTwice(
    test_Identifier this)
{
/* $begin(test/Identifier/tc_identifierTwice) */
    corto_string v = "world";
    corto_t_var vars[] = {
        {"var", corto_value_value(corto_string_o, &v)},
        {NULL}
    };

    corto_t_frame ctx = {findvar, vars};

    /* Compile template */
    corto_t *t = corto_t_compile("Hello ${var} ${var}!");
    test_assert(t != NULL);

    /* Run template with context and print result */
    corto_string str = corto_t_run(t, &ctx);
    test_assert(str != NULL);
    test_assertstr(str, "Hello world world!");

    corto_dealloc(str);
    corto_t_free(t);

/* $end */
}
