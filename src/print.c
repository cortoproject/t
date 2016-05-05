
#include "corto/t/t.h"

#include "intern.h"

static void corto_t_printslice(corto_t_slice slice) {
    corto_uint32 i = 0;
    corto_int32 len = slice.len;

    if (len < 0) {
        printf("warning: len of slice < 0 (%d)\n", slice.len);
        len = 5;
    }

    for (i = 0; i < len; i++) {
        putc(slice.ptr[i], stdout);
    }
}

static void corto_t_printop(corto_t_op *op) {
    switch(op->kind) {
    case CORTO_T_TEXT:
        printf("> TXT '");
        corto_t_printslice(op->data.text.t);
        printf("'\n");
        break;
    case CORTO_T_VAR:
        printf("> VAR '");
        corto_t_printslice(op->data.var.key);
        printf("'\n");
        break;
    case CORTO_T_FUNCTION:
        printf("> FUNC '%s' '", corto_idof(op->data.function.function));
        corto_t_printslice(op->data.function.arg);
        printf("'\n");
        break;
    }
}

void corto_t_print(corto_t *t) {
    corto_t_opbuff *current = &t->ops;

    printf("## Compile '%s'\n", t->template);
    do {
        corto_uint32 i = 0;
        while (i < current->count) {
            corto_t_op *op = &current->ops[i];
            corto_t_printop(op);
            i ++;
        }
    } while ((current = current->next));
}
