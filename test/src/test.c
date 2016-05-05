/* $CORTO_GENERATED
 *
 * test.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <test.h>

/* $header() */
corto_t_var* findvar(corto_string key, void *data) {
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

int testMain(int argc, char* argv[]) {
/* $begin(main) */
    int result = 0;
    test_Runner runner = test_RunnerCreate("corto/t", argv[0], (argc > 1) ? argv[1] : NULL);
    if (!runner) return -1;
    if (corto_llSize(runner->failures)) {
        result = -1;
    }
    corto_delete(runner);
    return result;
/* $end */
}
