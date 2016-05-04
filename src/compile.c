
#include "corto/t/t.h"

#include "intern.h"

#define CORTO_T_VAR_CURRENT ((corto_t_slice){NULL, 0})

static void corto_t_newOpbuffer(corto_t *t) {
    corto_t_opbuffer *ob = corto_alloc(sizeof(corto_t_opbuffer));
    ob->opcount = 0;
    ob->next = NULL;
    t->current->next = ob;
    t->current = ob;
}

static corto_t_op* corto_t_nextOp(corto_t *t) {
    corto_uint32 count = ++t->current->opcount;

    if (count > CORTO_T_OP_BUFF_COUNT) {
        corto_t_newOpbuffer(t);
        count = 1;
    }

    return &t->current->ops[count - 1];
}

static void corto_t_addText(corto_t *t, char *start, corto_uint32 len) {
    if (len) {
        corto_t_op *op = corto_t_nextOp(t);
        op->kind = CORTO_T_TEXT;
        op->data.text.t = (corto_t_slice){start, len};
    }
}

static void corto_t_addVar(corto_t *t, char *start, corto_uint32 len) {
    if (len) {
        corto_t_op *op = corto_t_nextOp(t);
        op->kind = CORTO_T_VAR;
        op->data.var.key = (corto_t_slice){start, len};
    }
}

static void corto_t_err(corto_t *t, char *msg, char *start) {
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


static char* corto_t_id(corto_t *t, char *start) {
    char *ptr = start;
    char ch = *ptr;

    if ((ch != '.') && !isalpha(ch)) {
        corto_t_err(t, "invalid identifier", start);
        goto error;
    }

    for (ptr = start + 1; (ch = *ptr) && !isspace(ch); ptr++) {
        if ((ch != '.') && !isalpha(ch) && !isdigit(ch)) {
            corto_t_err(t, "invalid identifier", start);
            break;
        }
    }

    return ptr - 1 /* Return last parsed character */;
error:
    return NULL;
}

static char* corto_t_text(corto_t *t, char *start) {
    char *ptr, ch;

    for (ptr = start; (ch = *ptr); ptr ++) {
        if (ch == CORTO_T_SIGIL) break;
        if (ch == '\\') {
            corto_t_addText(t, start, ptr - start);
            ptr += 1; /* Escape next character */
            start = ptr;
        }
    }

    /* Add text op */
    corto_t_addText(t, start, ptr - start);

    /* Return last parsed character */
    return ptr - 1;
}

static corto_int16 corto_t_codeblock(corto_t *t, corto_t_slice fwd) {
    return 0;
}

static corto_int16 corto_t_forward(corto_t *t, corto_t_slice fwd, corto_t_slice arg) {
    return 0;
}

static corto_int16 corto_t_filter(corto_t *t, corto_t_slice id, corto_t_slice filter) {
    return 0;
}

static corto_int16 corto_t_func(
    corto_t *t,
    corto_t_slice func,
    corto_t_slice arg)
{
    return 0;
}

static corto_int16 corto_t_comparator(
    corto_t *t,
    corto_t_slice func,
    corto_t_slice arg1,
    corto_t_slice comparator)
{
    return 0;
}

static corto_int16 corto_t_comparator_2arg(
    corto_t *t,
    corto_t_slice func,
    corto_t_slice arg1,
    corto_t_slice comparator,
    corto_t_slice arg2)
{
    return 0;
}

static char* corto_t_section_parseForward(corto_t *t, char *start) {
    corto_t_slice fwd, arg;

    char *end = corto_t_id(t, start);
    if (!end) {
        goto error;
    } else {
        fwd = (corto_t_slice){start, start - end};
    }

    char *ptr = corto_t_skipspace(end);
    if (*ptr == CORTO_T_CLOSE) {
        corto_t_codeblock(t, fwd);
    } else {
        char *end = corto_t_id(t, ptr);
        if (!end) {
            goto error;
        } else {
            arg = (corto_t_slice){ptr, ptr - end};
        }

        corto_t_forward(t, fwd, arg);
    }

    return ptr;
error:
    return NULL;
}

static char* corto_t_section_parseFilter(
    corto_t *t,
    char *start,
    corto_t_slice id)
{
    corto_t_slice filter;
    char *ptr = corto_t_skipspace(start);

    /* Parse filter identifier */
    char *end = corto_t_id(t, ptr);
    if (!end) {
        goto error;
    } else {
        filter = (corto_t_slice){ptr, ptr - end};
    }

    corto_t_filter(t, id, filter);

    return corto_t_skipspace(end);
error:
    return NULL;
}

static char* corto_t_section_parseComparator(
    corto_t *t,
    char *start,
    corto_t_slice func,
    corto_t_slice arg1)
{
    char *ptr = corto_t_skipspace(start);
    corto_t_slice comparator, arg2;

    /* Parse comparator id */
    char *end = corto_t_id(t, ptr);
    if (!end) {
        goto error;
    } else {
        comparator = (corto_t_slice){ptr, ptr - end};
    }

    ptr = corto_t_skipspace(end + 1);

    /* If section closes, found a comparator with a single argument */
    if (*ptr == CORTO_T_CLOSE) {
        corto_t_comparator(t, func, arg1, comparator);

    /* If section doesn't close, a comparator argument is expected */
    } else {
        /* Parse 2nd comparator argument */
        end = corto_t_id(t, ptr);
        if (!end) {
            goto error;
        } else {
            arg2 = (corto_t_slice){ptr, ptr - end};
        }

        ptr = corto_t_skipspace(end + 1);
        if (*ptr == CORTO_T_CLOSE) {
            corto_t_comparator_2arg(t, func, arg1, comparator, arg2);

        /* No more tokens expected */
        } else {
            corto_t_err(t, "unexpected token", ptr);
            goto error;
        }
    }

    return ptr;
error:
    return NULL;
}

static char* corto_t_section_parseFunction(
    corto_t *t,
    char *start,
    corto_t_slice func)
{
    corto_t_slice id;

    /* Parse argument for function */
    char *ptr, *end = corto_t_id(t, start);
    if (!end) {
        goto error;
    } else {
        id = (corto_t_slice){start, start - end};
    }

    ptr = corto_t_skipspace(end + 1);

    /* If closing curly brace is found, there are no comparators */
    if (*ptr == CORTO_T_CLOSE) {
        corto_t_func(t, func, id);

    /* If section doesn't close, expect comparator */
    } else if ((ptr[0] == 'i') && (ptr[1] == 's')) {
        ptr = corto_t_section_parseComparator(t, ptr + 2, func, id);

    } else {
        corto_t_err(t, "unexpected token", ptr);
        goto error;
    }

    return ptr;
error:
    return NULL;
}

static char* corto_t_section(corto_t *t, char *start) {
    /* Slice for identifier */
    corto_t_slice id;

    /* {} section may start with whitespace */
    char *ptr = corto_t_skipspace(start);

    if (*ptr == '>') {
        ptr = corto_t_section_parseForward(t, ptr + 1);
    } else {

        /* Parse first identifier */
        char *end = corto_t_id(t, ptr);
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
            corto_t_addVar(t, id.ptr, id.len);

        /* If next token is a '|', this section is a filter */
        } else if (*ptr == '|') {
            ptr = corto_t_section_parseFilter(t, ptr, id);

        /* Otherwise, a function call is expected */
        } else {
            ptr = corto_t_section_parseFunction(t, ptr, id);
        }
    }

    return ptr;
error:
    return NULL;
}

static char* corto_t_sigil(corto_t *t, char *start) {
    char *ptr = start + 1; /* Skip sigil */
    char ch = *ptr;

    /* When '$' is followed by a whitespace, insert current value */
    if (isspace(ch)) {
        ptr --; /* Give back whitespace */
        corto_t_addVar(t, NULL, 0);

    /* Open a section with {} */
    } else if (ch == CORTO_T_OPEN) {
        ptr = corto_t_section(t, ptr + 1);

    /* '$' is followed by an identifier */
    } else {
        char *end = corto_t_id(t, ptr);
        if (!end) {
            goto error;
        }

        corto_t_addVar(t, ptr, 1 + end - ptr);
        ptr = end;
    }

    return ptr;
error:
    return NULL;
}

corto_t* corto_t_compile(corto_string template) {
    char *ptr, ch;

    corto_t *t = corto_calloc(sizeof(corto_t));
    t->template = corto_strdup(template);
    t->current = &t->ops;

    for (ptr = template; (ch = *ptr); ptr ++) {
        switch(ch) {
        case CORTO_T_SIGIL:
            ptr = corto_t_sigil(t, ptr);
            if (!ptr) {
                goto error;
            }
            break;
        default:
            ptr = corto_t_text(t, ptr);
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
    corto_t_opbuffer *b, *next;

    for (next = t->ops.next; (b = next); next = b->next, corto_dealloc(b));

    corto_dealloc(t);
}
