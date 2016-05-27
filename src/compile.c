
#include "corto/t/t.h"

#include "intern.h"

#define CORTO_T_VAL_CURRENT ((corto_t_slice){NULL, 0})

typedef struct corto_t_compile_t {
    corto_t *t;
    corto_t_opbuff *currentOp;
    corto_t_importbuff *currentImport;
    corto_t_op *stack[CORTO_T_FRAME_DEPTH];
    corto_uint32 sp;
} corto_t_compile_t;

static corto_t_op* corto_t_addVal(corto_string start, corto_uint32 len, corto_t_opKind flag, corto_t_compile_t *data);

static void corto_t_err(corto_t_compile_t *t, char *msg, char *start) {
    char buff[20];
    char *ptr, *bptr = buff, ch;

    if (start) {
        for(ptr = start; (ch = *ptr) && ((ptr - start) < 16); ptr++) {
            *bptr = ch;
            bptr++;
        }

        if (ch) {
            *(bptr++) = '.';
            *(bptr++) = '.';
            *(bptr++) = '.';
        }
        *(bptr++) = '\0';
        corto_seterr("%s near '%s'", msg, buff);
    } else {
        corto_seterr("%s", msg);
    }

}

static void corto_t_newOpbuffer(corto_t_compile_t *data) {
    corto_t_opbuff *ob = corto_alloc(sizeof(corto_t_opbuff));
    ob->count = 0;
    ob->next = NULL;
    data->currentOp->next = ob;
    data->currentOp = ob;
}

static corto_t_op* corto_t_nextOp(corto_t_compile_t *data) {
    corto_uint32 count = ++data->currentOp->count;

    if (count > CORTO_T_OP_BUFF_COUNT) {
        corto_t_newOpbuffer(data);
        count = 1;
    }

    return &data->currentOp->ops[count - 1];
}

static void corto_t_newImportbuffer(corto_t_compile_t *data) {
    corto_t_importbuff *ib = corto_alloc(sizeof(corto_t_importbuff));
    ib->count = 0;
    ib->next = NULL;
    data->currentImport->next = ib;
    data->currentImport = ib;
}

static corto_object* corto_t_nextImport(corto_t_compile_t *data) {
    corto_uint32 count = ++data->currentImport->count;

    if (count > CORTO_T_IMPORT_BUFF_COUNT) {
        corto_t_newImportbuffer(data);
        count = 1;
    }

    return &data->currentImport->imports[count - 1];
}

static corto_object corto_t_resolve(
    corto_string id,
    corto_type t,
    corto_t_compile_t *data)
{
    corto_t_importbuff *buf = &data->t->imports;
    corto_uint32 i = 0;
    corto_object result = NULL;

    do {
        while (!result && (i < buf->count)) {
            corto_object op = buf->imports[i];
            result = corto_lookup(op, id);
            if (result && !corto_instanceof(t, result)) {
                corto_t_err(data, "identifier of unexpected type", id);
                goto error;
            }
            i ++;
        }
    } while (!result && (buf = buf->next));

    return result;
error:
    return NULL;
}

static char* corto_t_token(
    char *start,
    corto_bool alpha,
    corto_bool num,
    corto_char delim,
    char **member,
    corto_t_compile_t *data)
{
    char *ptr = start;
    char ch = *ptr;

    if (member) {
        *member = NULL;
    }

    for (ptr = start + 1; (ch = *ptr) && !isspace(ch) && (ch != '}') && (ch != delim); ptr++) {
        if (ch == '.') {
            if (member && !*member) {
                *member = ptr;
            }
        } else if ((ch != '/') && (alpha && !isalpha(ch)) && (num && !isdigit(ch))) {
            break;
        }
    }

    if (member) {
        /* If the identifier is just 1 character long, it contains no members */
        if ((ptr - start) == 1) {
            *member = NULL;
        }
    }

    return ptr - 1; /* Return last parsed character */
}

static char* corto_t_id(char *start, corto_t_compile_t *data) {
    char *ptr = start;
    char ch = *ptr;

    if ((ch != '/') && (ch != '.') && !isalpha(ch)) {
        corto_t_err(data, "invalid identifier", start);
        goto error;
    }

    ptr = corto_t_token(ptr, TRUE, TRUE, '\0', NULL, data);

    return ptr;
error:
    return NULL;
}

static char* corto_t_numExpr(char *start, corto_t_expr *out, corto_t_compile_t *data) {
    char *ptr = start;
    corto_id num;

    ptr = corto_t_token(ptr, TRUE, TRUE, '\0', NULL, data);
    if (!ptr) {
        goto error;
    }

    corto_t_copySliceToString(num, (corto_t_slice){start, ptr - start});

    out->kind = CORTO_T_LITERAL;
    out->expr.literal.type = corto_type(corto_float64_o);
    out->expr.literal.value._float = atof(num);

    return ptr - 1;
error:
    return NULL;
}

static char* corto_t_strExpr(char *start, corto_t_expr *out, corto_t_compile_t *data) {
    char *ptr = start;

    ptr = corto_t_token(ptr, TRUE, TRUE, '"', NULL, data);
    if (!ptr) {
        goto error;
    }

    out->kind = CORTO_T_LITERAL;
    out->expr.literal.type = corto_type(corto_string_o);
    out->expr.literal.value._string.ptr = start + 1;
    out->expr.literal.value._string.len = ptr - start - 1;

    return ptr - 1;
error:
    return NULL;
}

static corto_int16 corto_t_parseObject(char *start, char *ptr, corto_type t, corto_t_expr *out, corto_t_compile_t *data) {
    corto_t_slice idSlice = {start, 1 + ptr - start};
    corto_id id;
    corto_t_copySliceToString(id, idSlice);

    out->kind = CORTO_T_OBJECT;

    out->expr.object = corto_resolve(NULL, id);
    if (!out->expr.object) {
        corto_seterr("object '%s' not found", id);
        goto error;
    } else if (t && !corto_instanceof(t, out->expr.object)) {
        corto_seterr("object '%s' is not of type '%s'",
            corto_fullpath(NULL, out->expr.object),
            corto_fullpath(NULL, t));
        goto error;
    }

    return 0;
error:
    return -1;
}

static char* corto_t_parseExpr(char *start, corto_type t, corto_t_expr *out, corto_t_compile_t *data) {
    char *ptr = start;
    char ch = *ptr;
    char *member = NULL;

    if (ch == '"') {
        ptr = corto_t_strExpr(start, out, data);
    } else if (ch == '/') {
        ptr = corto_t_token(ptr, TRUE, TRUE, '\0', &member, data);
        if (corto_t_parseObject(start, member ? member - 1: ptr, t, out, data)) {
            goto error;
        }
        if (member) {
            out->kind = CORTO_T_OBJECT_MEMBER;
            out->expr.object_member.member.ptr = member;
            out->expr.object_member.member.len = 1 + ptr - member;
        }
    } else if (ch == '\0') {
        out->kind = CORTO_T_IDENTIFIER;
        out->expr.identifier.ptr = start;
        out->expr.identifier.len = 1 + ptr - start;
    } else if (isdigit(ch)) {
        ptr = corto_t_numExpr(start, out, data);
    } else if (isalpha(ch)) {
        ptr = corto_t_token(ptr, TRUE, TRUE, '\0', &member, data);
        if (ptr) {
            if ((ptr - start == 4) && !memcmp(start, "true", ptr - start)) {
                out->kind = CORTO_T_LITERAL;
                out->expr.literal.type = corto_type(corto_bool_o);
                out->expr.literal.value._bool = TRUE;
            } else if ((ptr - start == 5) && !memcmp(start, "false", ptr - start)) {
                out->kind = CORTO_T_LITERAL;
                out->expr.literal.type = corto_type(corto_bool_o);
                out->expr.literal.value._bool = FALSE;
            } else {
                if (t && t->reference) {
                    if (corto_t_parseObject(start, member ? member - 1: ptr, t, out, data)) {
                        goto error;
                    }
                    if (member) {
                        out->kind = CORTO_T_OBJECT_MEMBER;
                        out->expr.object_member.member.ptr = member;
                        out->expr.object_member.member.len = 1 + ptr - member;
                    }
                } else {
                    if (!member) {
                        out->kind = CORTO_T_IDENTIFIER;
                        out->expr.identifier.ptr = start;
                        out->expr.identifier.len = 1 + ptr - start;
                    } else {
                        out->kind = CORTO_T_IDENTIFIER_MEMBER;
                        out->expr.identifier_member.identifier.ptr = start;
                        out->expr.identifier_member.identifier.len = 1 + ptr - start;
                        out->expr.identifier_member.idLen = member - start;
                    }
                }
            }
        } else {
            goto error;
        }
    }

    return ptr;
error:
    return NULL;
}

static corto_int16 corto_t_pushFunc(corto_t_op *op, corto_t_compile_t *data) {
    corto_assert(op->kind == CORTO_T_FUNCTION, "pushed operation is not a function");
    if (data->sp == CORTO_T_FRAME_DEPTH) {
        corto_seterr("block exceeds maximum nesting level");
        goto error;
    }
    data->stack[data->sp ++] = op;
    return 0;
error:
    return -1;
}

static corto_t_op* corto_t_popFunc(corto_t_compile_t *data) {
    corto_t_op *op = data->stack[data->sp - 1];

    op->data.function.block.stopBuff = data->currentOp;
    op->data.function.block.stopOp = data->currentOp->count;

    data->sp --;
    return op;
}

static void corto_t_addText(char *start, corto_uint32 len, corto_t_compile_t *data) {
    if (len) {
        corto_t_op *op = corto_t_nextOp(data);
        op->kind = CORTO_T_TEXT;
        op->data.text.t = (corto_t_slice){start, len};
    }
}

static corto_int16 corto_t_prepareChain(
    corto_t_function f,
    corto_t_compile_t *data)
{
    if (f->chain) {
        if (data->sp) {
            corto_t_op *op = data->stack[data->sp - 1];
            corto_t_function cur = op->data.function.function;
            if (f->chainType == corto_function(cur)->returnType) {
                /* Take current function from stack */
                corto_t_popFunc(data);

                /* Write result to chain */
                op->kind = CORTO_T_FUNCTION_CHAIN;
            } else {
                corto_seterr("unmatching '%s' with '%s' (%s vs. %s)",
                    corto_idof(cur),
                    corto_idof(f),
                    corto_fullpath(NULL, corto_function(cur)->returnType),
                    corto_fullpath(NULL, corto_function(f)->returnType));
                goto error;
            }
        } else {
            corto_seterr("dangling '%s'", corto_idof(f));
            goto error;
        }
    }

    return 0;
error:
    return -1;
}

static corto_t_op* corto_t_addFunction(
    corto_t_function f,
    corto_t_compile_t *data)
{
    corto_t_op *op = corto_t_nextOp(data);
    op->kind = CORTO_T_FUNCTION;
    op->data.function.function = f;
    op->data.function.block.startBuff = data->currentOp;
    op->data.function.block.startOp = data->currentOp->count;
    op->data.function.block.stopBuff = NULL;
    op->data.function.block.stopOp = 0;

    if (f->requiresBlock) {
        if (corto_t_pushFunc(op, data)) {
            goto error;
        }
    }

    return op;
error:
    return NULL;
}

static corto_t_op* corto_t_addFilter(
    corto_function f,
    corto_t_compile_t *data)
{
    corto_t_op *op = corto_t_nextOp(data);
    op->kind = CORTO_T_FILTER;
    op->data.filter.filter = f;

    return op;
}

static corto_t_op* corto_t_addComparator(
    corto_t_comparator c,
    corto_t_slice arg,
    corto_t_compile_t *data)
{
    corto_t_op *op = corto_t_nextOp(data);
    op->kind = CORTO_T_COMPARATOR;
    op->data.comparator.comparator = c;

    if (arg.ptr) {
        if (!corto_t_parseExpr(arg.ptr, c->argType, &op->data.comparator.arg, data)) {
            goto error;
        }
    }

    return op;
error:
    return NULL;
}

static corto_t_op* corto_t_addVal(corto_string start, corto_uint32 len, corto_t_opKind flag, corto_t_compile_t *data) {
    corto_id varId;
    corto_t_function f;
    corto_t_op *result = NULL;
    corto_t_copySliceToString(varId, (corto_t_slice){start, len});

    if ((len == 3) && (!memcmp(start, "end", 3))) {
        if (data->sp) {
            result = corto_t_popFunc(data);
        } else {
            corto_t_err(data, "end token without block", start);
            goto error;
        }
    } else if (len && (f = corto_t_resolve(varId, corto_type(corto_t_function_o), data))) {
        if (corto_t_prepareChain(f, data)) {
            goto error;
        }
        if (!(result = corto_t_addFunction(f, data))) {
            goto error;
        }
    } else {
        corto_t_op *op = corto_t_nextOp(data);
        op->kind = CORTO_T_VAL | flag;
        if (!corto_t_parseExpr(start, NULL, &op->data.val.expr, data)) {
            goto error;
        }
        result = op;
    }

    return result;
error:
    return NULL;
}

void corto_t_copySliceToString(corto_id buf, corto_t_slice slice) {
    strncpy(buf, slice.ptr, slice.len);
    buf[slice.len] = '\0';
}

static char* corto_t_skipspace(char *start) {
    char *ptr, ch;
    for (ptr = start; (ch = *ptr) && isspace(ch); ptr++) ;
    return ptr;
}

static corto_int16 corto_t_import(corto_string import, corto_t_compile_t *data) {
    if (corto_load(import, 0, NULL)) {
        corto_t_err(data, "unresolved import", import);
        goto error;
    }

    corto_object o = corto_resolve(NULL, import);

    if (o) {
        *corto_t_nextImport(data) = o;
    } else {
        corto_t_err(data, "failed to load import", import);
        goto error;
    }

    return 0;
error:
    return -1;
}

static char* corto_t_text(char *start, corto_t_compile_t *data) {
    char *ptr, ch;

    for (ptr = start; (ch = *ptr); ptr ++) {
        if (ch == CORTO_T_SIGIL) break;
        if (ch == '\\') {
            corto_t_addText(start, ptr - start, data);
            ptr += 1; /* Escape next character */
            start = ptr;
        }
    }

    /* Add text op */
    corto_t_addText(start, ptr - start, data);

    /* Return last parsed character */
    return ptr - 1;
}

static corto_int16 corto_t_codeblock(corto_t_slice fwd, corto_t_compile_t *data) {
    return 0;
}

static corto_int16 corto_t_forward(corto_t_slice fwd, corto_t_slice arg, corto_t_compile_t *data) {
    return 0;
}

static corto_int16 corto_t_filter(corto_t_slice id, corto_t_slice filter, corto_t_compile_t *data) {
    corto_function f;
    corto_id filterId;

    corto_t_copySliceToString(filterId, filter);

    f = corto_t_resolve(filterId, corto_type(corto_function_o), data);
    if (!f) {
        corto_t_err(data, "unknown function", filter.ptr);
        goto error;
    }

    if (!corto_t_addFilter(f, data)) {
        goto error;
    }

    return 0;
error:
    return -1;
}

static corto_int16 corto_t_func(
    corto_t_slice func,
    corto_t_slice arg,
    corto_t_compile_t *data)
{
    corto_t_function f;
    corto_id funcId;

    corto_t_copySliceToString(funcId, func);

    f = corto_t_resolve(funcId, corto_type(corto_t_function_o), data);
    if (!f) {
        corto_t_err(data, "unknown function", func.ptr);
        goto error;
    }

    if (corto_t_prepareChain(f, data)) {
        goto error;
    }

    if (!corto_t_addVal(arg.ptr, arg.len, CORTO_T_TOREG, data)) {
        goto error;
    }

    if (!corto_t_addFunction(f, data)) {
        goto error;
    }

    return 0;
error:
    return -1;
}

static corto_int16 corto_t_comp_2arg(
    corto_t_slice func,
    corto_t_slice arg1,
    corto_t_slice comparator,
    corto_t_slice arg2,
    corto_t_compile_t *data)
{
    corto_t_function f;
    corto_t_comparator c;
    corto_id funcId, comparatorId;
    corto_t_op *funcOp, *compOp;

    corto_t_copySliceToString(funcId, func);
    corto_t_copySliceToString(comparatorId, comparator);

    f = corto_t_resolve(funcId, corto_type(corto_t_function_o), data);
    if (!f) {
        corto_t_err(data, "unknown function", func.ptr);
        goto error;
    }

    c = corto_t_resolve(comparatorId, corto_type(corto_t_comparator_o), data);
    if (!c) {
        corto_t_err(data, "unknown comparator", comparator.ptr);
        goto error;
    }

    if (corto_t_prepareChain(f, data)) {
        goto error;
    }

    if (!corto_t_addVal(arg1.ptr, arg1.len, CORTO_T_TOREG, data)) {
        goto error;
    }

    if (!(compOp = corto_t_addComparator(c, arg2, data))) {
        goto error;
    }

    if (!(funcOp = corto_t_addFunction(f, data))) {
        goto error;
    }

    return 0;
error:
    return -1;
}

static corto_int16 corto_t_comp(
    corto_t_slice func,
    corto_t_slice arg1,
    corto_t_slice comparator,
    corto_t_compile_t *data)
{
    return corto_t_comp_2arg(func, arg1, comparator, (corto_t_slice){NULL, 0}, data);
}

static char* corto_t_section_forward(char *start, corto_t_compile_t *data) {
    corto_t_slice fwd, arg;

    char *end = corto_t_id(start, data);
    if (!end) {
        goto error;
    } else {
        fwd = (corto_t_slice){start, start - end};
    }

    char *ptr = corto_t_skipspace(end);
    if (*ptr == CORTO_T_CLOSE) {
        corto_t_codeblock(fwd, data);
    } else {
        char *end = corto_t_id(ptr, data);
        if (!end) {
            goto error;
        } else {
            arg = (corto_t_slice){ptr, ptr - end};
        }

        corto_t_forward(fwd, arg, data);
    }

    return ptr;
error:
    return NULL;
}

static char* corto_t_section_filter(
    char *start,
    corto_t_slice id,
    corto_t_compile_t *data)
{
    corto_t_slice filter;
    char *ptr = corto_t_skipspace(start);

    do {
        if (*ptr == '|') ptr ++;

        /* Parse filter identifier */
        char *end = corto_t_id(ptr, data);
        if (!end) {
            goto error;
        } else {
            filter = (corto_t_slice){ptr, 1 + end - ptr};
        }

        corto_t_filter(id, filter, data);

        ptr = corto_t_skipspace(end + 1);
    } while (*ptr && *ptr == '|');

    /* Filters must end with a close token */
    if (*ptr != CORTO_T_CLOSE) {
        corto_t_err(data, "unexpected token after filter", start);
        goto error;
    }

    return ptr;
error:
    return NULL;
}

static char* corto_t_section_comparator(
    char *start,
    corto_t_slice func,
    corto_t_slice arg1,
    corto_t_compile_t *data)
{
    char *ptr = corto_t_skipspace(start);
    corto_t_slice comparator, arg2;

    /* Parse comparator id */
    char *end = corto_t_id(ptr, data);
    if (!end) {
        goto error;
    } else {
        comparator = (corto_t_slice){ptr, 1 + end - ptr};
    }

    ptr = corto_t_skipspace(end + 1);

    /* If section closes, found a comparator with a single argument */
    if (*ptr == CORTO_T_CLOSE) {
        if (corto_t_comp(func, arg1, comparator, data)) {
            return NULL;
        }

    /* If section doesn't close, a comparator argument is expected */
    } else {
        /* Parse 2nd comparator argument */
        end = corto_t_id(ptr, data);
        if (!end) {
            goto error;
        } else {
            arg2 = (corto_t_slice){ptr, 1 + end - ptr};
        }

        ptr = corto_t_skipspace(end + 1);
        if (*ptr == CORTO_T_CLOSE) {
            if (corto_t_comp_2arg(func, arg1, comparator, arg2, data)) {
                goto error;
            }

        /* No more tokens expected */
        } else {
            corto_t_err(data, "unexpected token", ptr);
            goto error;
        }
    }

    return ptr;
error:
    return NULL;
}

static char* corto_t_section_func(
    char *start,
    corto_t_slice func,
    corto_t_compile_t *data)
{
    corto_t_slice id;

    /* Parse argument for function */
    char *ptr, *end = corto_t_id(start, data);
    if (!end) {
        goto error;
    } else {
        id = (corto_t_slice){start, 1 + end - start};
    }

    ptr = corto_t_skipspace(end + 1);

    /* If closing curly brace is found, there are no comparators */
    if (*ptr == CORTO_T_CLOSE) {
        if (corto_t_func(func, id, data)) {
            goto error;
        }

    /* If section doesn't close, expect comparator */
    } else if ((ptr[0] == 'i') && (ptr[1] == 's')) {
        ptr = corto_t_section_comparator(ptr + 2, func, id, data);

    } else {
        corto_t_err(data, "unexpected token", ptr);
        goto error;
    }

    return ptr;
error:
    return NULL;
}

static char* corto_t_section(char *start, corto_t_compile_t *data) {
    /* Slice for identifier */
    corto_t_slice id;

    /* {} section may start with whitespace */
    char *ptr = corto_t_skipspace(start);

    if (*ptr == '>') {
        ptr = corto_t_section_forward(ptr + 1, data);
    } else {

        /* Parse first identifier */
        char *end = corto_t_id(ptr, data);
        if (!end) {
            goto error;
        } else {
            id = (corto_t_slice){ptr, 1 + end - ptr};
        }

        /* Account for spaces */
        ptr = corto_t_skipspace(end + 1);

        /* If an identifier just appears by itself in a section, create a var
         * operation for it */
        if (*ptr == CORTO_T_CLOSE) {
            /* Add value to template program */
            if (!corto_t_addVal(id.ptr, id.len, CORTO_T_TOBUFF, data)) {
                goto error;
            }

        /* If next token is a '|', this section is a filter */
        } else if (*ptr == '|') {
            if (!corto_t_addVal(id.ptr, id.len, CORTO_T_TOREG, data)) {
                goto error;
            }

            ptr = corto_t_section_filter(ptr + 1, id, data);

        /* Otherwise, a function call is expected */
        } else {
            ptr = corto_t_section_func(ptr, id, data);
        }
    }

    return ptr;
error:
    return NULL;
}

static char* corto_t_sigil(char *start, corto_t_compile_t *data) {
    char *ptr = start + 1; /* Skip sigil */
    char ch = *ptr;

    /* When '$' is followed by a whitespace, insert current value */
    if (isspace(ch)) {
        ptr --; /* Give back whitespace */
        if (!corto_t_addVal("", 0, CORTO_T_TOBUFF, data)) {
            goto error;
        }

    /* Open a section with {} */
    } else if (ch == CORTO_T_OPEN) {
        ptr = corto_t_section(ptr + 1, data);

    /* '$' is followed by an identifier */
    } else {
        char *end = corto_t_id(ptr, data);
        if (!end) {
            goto error;
        }

        if (!corto_t_addVal(ptr, 1 + end - ptr, CORTO_T_TOBUFF, data)) {
            goto error;
        }
        ptr = end;
    }

    return ptr;
error:
    return NULL;
}

corto_t* corto_t_compile(corto_string template) {
    char *ptr, ch;

    corto_t *t = corto_calloc(sizeof(corto_t));
    corto_t_compile_t data = {t, &t->ops, &t->imports};
    t->template = corto_strdup(template);

    /* Always import std */
    if (corto_t_import("corto/t/std", &data)) {
        corto_dealloc(t->template);
        corto_dealloc(t);
        goto error;
    }

    for (ptr = template; (ch = *ptr); ptr ++) {
        switch(ch) {
        case CORTO_T_SIGIL:
            ptr = corto_t_sigil(ptr, &data);
            if (!ptr) {
                goto error;
            }
            break;
        default:
            ptr = corto_t_text(ptr, &data);
            if (!ptr) {
                goto error;
            }
            break;
        }
    }

    return t;
error:
    return NULL;
}

void corto_t_free(corto_t *t) {
    corto_t_opbuff *b, *next;

    for (next = t->ops.next; (b = next); next = b->next, corto_dealloc(b));

    corto_dealloc(t);
}
