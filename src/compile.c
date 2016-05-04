
#include "corto/t/t.h"

#include "intern.h"

#define CORTO_T_VAR_CURRENT ((corto_t_slice){NULL, 0})

typedef struct corto_t_compile_t {
    corto_t *t;
    corto_t_opbuff *currentOp;
    corto_t_importbuff *currentImport;
} corto_t_compile_t;

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

static void corto_t_addText(char *start, corto_uint32 len, corto_t_compile_t *data) {
    if (len) {
        corto_t_op *op = corto_t_nextOp(data);
        op->kind = CORTO_T_TEXT;
        op->data.text.t = (corto_t_slice){start, len};
    }
}

static void corto_t_addVar(char *start, corto_uint32 len, corto_t_compile_t *data) {
    if (len) {
        corto_t_op *op = corto_t_nextOp(data);
        op->kind = CORTO_T_VAR;
        op->data.var.key = (corto_t_slice){start, len};
    }
}

static void corto_t_slicecpy(corto_id buf, corto_t_slice slice) {
    strncpy(buf, slice.ptr, slice.len);
    buf[slice.len] = '\0';
}

static void corto_t_err(corto_t_compile_t *t, char *msg, char *start) {
    char buff[20];
    char *ptr, *bptr = buff, ch;

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
}

static char* corto_t_skipspace(char *start) {
    char *ptr, ch;
    for (ptr = start; (ch = *ptr) && isspace(ch); ptr++) ;
    return ptr;
}

static corto_int16 corto_t_import(corto_string import, corto_t_compile_t *data) {
    corto_object o = corto_resolve(NULL, import);

    if (o) {
        *corto_t_nextImport(data) = o;
    } else {
        corto_t_err(data, "unresolved import", import);
        goto error;
    }

    return 0;
error:
    return -1;
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
                corto_t_err(data, "unexpected type", id);
                goto error;
            }
            i ++;
        }
    } while (!result && (buf = buf->next));

    return result;
error:
    return NULL;
}

static char* corto_t_id(char *start, corto_t_compile_t *data) {
    char *ptr = start;
    char ch = *ptr;

    if ((ch != '.') && !isalpha(ch)) {
        corto_t_err(data, "invalid identifier", start);
        goto error;
    }

    for (ptr = start + 1; (ch = *ptr) && !isspace(ch); ptr++) {
        if ((ch != '.') && !isalpha(ch) && !isdigit(ch)) {
            corto_t_err(data, "invalid identifier", start);
            break;
        }
    }

    return ptr - 1 /* Return last parsed character */;
error:
    return NULL;
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
    return 0;
}

static corto_int16 corto_t_func(
    corto_t_slice func,
    corto_t_slice arg,
    corto_t_compile_t *data)
{
    corto_t_function f;
    corto_id funcId;

    corto_t_slicecpy(funcId, func);

    f = corto_t_resolve(funcId, corto_type(corto_t_function_o), data);
    if (!f) {
        goto error;
    }

    return 0;
error:
    return -1;
}

static corto_int16 corto_t_comparator(
    corto_t_slice func,
    corto_t_slice arg1,
    corto_t_slice comparator,
    corto_t_compile_t *data)
{
    return 0;
}

static corto_int16 corto_t_comparator_2arg(
    corto_t_slice func,
    corto_t_slice arg1,
    corto_t_slice comparator,
    corto_t_slice arg2,
    corto_t_compile_t *data)
{
    return 0;
}

static char* corto_t_section_parseForward(char *start, corto_t_compile_t *data) {
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

static char* corto_t_section_parseFilter(
    char *start,
    corto_t_slice id,
    corto_t_compile_t *data)
{
    corto_t_slice filter;
    char *ptr = corto_t_skipspace(start);

    /* Parse filter identifier */
    char *end = corto_t_id(ptr, data);
    if (!end) {
        goto error;
    } else {
        filter = (corto_t_slice){ptr, ptr - end};
    }

    corto_t_filter(id, filter, data);

    return corto_t_skipspace(end);
error:
    return NULL;
}

static char* corto_t_section_parseComparator(
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
        comparator = (corto_t_slice){ptr, ptr - end};
    }

    ptr = corto_t_skipspace(end + 1);

    /* If section closes, found a comparator with a single argument */
    if (*ptr == CORTO_T_CLOSE) {
        corto_t_comparator(func, arg1, comparator, data);

    /* If section doesn't close, a comparator argument is expected */
    } else {
        /* Parse 2nd comparator argument */
        end = corto_t_id(ptr, data);
        if (!end) {
            goto error;
        } else {
            arg2 = (corto_t_slice){ptr, ptr - end};
        }

        ptr = corto_t_skipspace(end + 1);
        if (*ptr == CORTO_T_CLOSE) {
            corto_t_comparator_2arg(func, arg1, comparator, arg2, data);

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

static char* corto_t_section_parseFunction(
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
        id = (corto_t_slice){start, start - end};
    }

    ptr = corto_t_skipspace(end + 1);

    /* If closing curly brace is found, there are no comparators */
    if (*ptr == CORTO_T_CLOSE) {
        corto_t_func(func, id, data);

    /* If section doesn't close, expect comparator */
    } else if ((ptr[0] == 'i') && (ptr[1] == 's')) {
        ptr = corto_t_section_parseComparator(ptr + 2, func, id, data);

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
        ptr = corto_t_section_parseForward(ptr + 1, data);
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
            /* Add variable to template program */
            corto_t_addVar(id.ptr, id.len, data);

        /* If next token is a '|', this section is a filter */
        } else if (*ptr == '|') {
            ptr = corto_t_section_parseFilter(ptr, id, data);

        /* Otherwise, a function call is expected */
        } else {
            ptr = corto_t_section_parseFunction(ptr, id, data);
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
        corto_t_addVar(NULL, 0, data);

    /* Open a section with {} */
    } else if (ch == CORTO_T_OPEN) {
        ptr = corto_t_section(ptr + 1, data);

    /* '$' is followed by an identifier */
    } else {
        char *end = corto_t_id(ptr, data);
        if (!end) {
            goto error;
        }

        corto_t_addVar(ptr, 1 + end - ptr, data);
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
    corto_t_import("/corto/t/std", &data);

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
