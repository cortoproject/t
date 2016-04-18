
#include "corto/t/t.h"

#include "intern.h"

static void corto_t_printslice(corto_t_slice slice) {
    corto_uint32 i = 0;
    for (i = 0; i < slice.len; i++) {
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
    }
}

void corto_t_print(corto_t *t) {
    corto_t_opbuffer *current = &t->ops;

    printf("## Compile '%s'\n", t->template);
    do {
        corto_uint32 i = 0;
        while (i < current->opcount) {
            corto_t_op *op = &current->ops[i];
            corto_t_printop(op);
            i ++;
        }
    } while ((current = current->next));
}
