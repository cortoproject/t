
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

static char* corto_t_printroute(corto_t_op *op) {
    corto_bool reg = FALSE;
    if (op->kind & CORTO_T_TOREG) {
        reg = TRUE;
    }
    if ((op->kind == CORTO_T_FUNCTION) || (op->kind == CORTO_T_FUNCTION_CHAIN))  {
        if (!op->data.function.function->echo) {
            return "  ";
        }
    }
    if (reg) {
        return "> ";
    } else {
        return "< ";
    }
}

static void corto_t_printop(corto_t_op *op) {
    corto_t_opKind kind = op->kind;
    if (op->kind & CORTO_T_TOREG) {
        kind -= CORTO_T_TOREG;
    }
    switch(kind) {
    case CORTO_T_TEXT:
        printf("%s TEXT     '", corto_t_printroute(op));
        corto_t_printslice(op->data.text.t);
        printf("'\n");
        break;
    case CORTO_T_VAL:
        printf("%s VALUE    '", corto_t_printroute(op));
        corto_t_printexpr(&op->data.val.expr);
        printf("'\n");
        break;
    case CORTO_T_FUNCTION_CHAIN:
        printf("%s CHAIN    '%s'\n", corto_t_printroute(op), corto_idof(op->data.function.function));
        break;
    case CORTO_T_FUNCTION:
        printf("%s FUNCTION '%s'\n", corto_t_printroute(op), corto_idof(op->data.function.function));
        break;
    case CORTO_T_COMPARATOR:
        printf("%s COMPARE  '%s'", corto_t_printroute(op), corto_idof(op->data.comparator.comparator));
        corto_t_printexpr(&op->data.comparator.arg);
        printf("'\n");
        break;
    case CORTO_T_PUSH:
        printf("   PUSH     '");
        corto_t_printexpr(&op->data.val.expr);
        printf("'\n");
        break;
    case CORTO_T_FILTER:
        printf("%s FILTER   '%s'\n", corto_t_printroute(op), corto_idof(op->data.filter.filter));
        break;
    default:
        corto_assert(FALSE, "invalid template operation (%d)", kind);
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
