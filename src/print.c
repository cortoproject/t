
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

static void corto_t_printexpr(corto_t_expr *expr) {
    switch(expr->kind) {
    case CORTO_T_LITERAL:
        switch(corto_primitive(expr->expr.literal.type)->kind) {
        case CORTO_BOOLEAN:
            printf("%s", expr->expr.literal.value._bool ? "true" : "false");
            break;
        case CORTO_FLOAT:
            printf("%f", expr->expr.literal.value._float);
            break;
        case CORTO_TEXT:
            printf("\"");
            corto_t_printslice(expr->expr.literal.value._string);
            printf("\"");
            break;
        default:
            printf("unsupported literal type '%s'", corto_fullpath(NULL, expr->expr.literal.type));
            break;
        }
        break;
    case CORTO_T_IDENTIFIER:
        corto_t_printslice(expr->expr.identifier);
        break;
    case CORTO_T_OBJECT:
        printf("%s", corto_fullpath(NULL, expr->expr.object));
        break;
    case CORTO_T_IDENTIFIER_MEMBER:
        corto_t_printslice(expr->expr.identifier_member.identifier);
        break;
    case CORTO_T_OBJECT_MEMBER:
        printf("%s.", corto_fullpath(NULL, expr->expr.object));
        corto_t_printslice(expr->expr.object_member.member);
        break;
    }
}

static void corto_t_printop(corto_t_op *op) {
    switch(op->kind) {
    case CORTO_T_TEXT:
        printf("> TXT '");
        corto_t_printslice(op->data.text.t);
        printf("'\n");
        break;
    case CORTO_T_VAL:
        printf("> VAR '");
        corto_t_printexpr(&op->data.val.expr);
        printf("'\n");
        break;
    case CORTO_T_FUNCTION:
        printf("> FUNC '%s' '", corto_idof(op->data.function.function));
        corto_t_printexpr(&op->data.function.arg);
        printf("'\n");
        break;
    case CORTO_T_FUNCTION_COMPARATOR:
        printf("> FUNC '%s' <comparator>\n", corto_idof(op->data.function.function));
        break;
    case CORTO_T_COMPARATOR:
        printf("> COMP '%s' '", corto_idof(op->data.comparator.comparator));
        corto_t_printexpr(&op->data.comparator.arg);
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
