
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
            ptr ++; /* Escape next character */
        }
    }

    /* Add text op */
    corto_t_addText(t, start, ptr - start);

    /* Return last parsed character */
    return ptr - 1;
}

static char* corto_t_section(corto_t *t, char *start) {
    char *ptr = start + 1; /* Skip sigil */
    char ch = *ptr;

    /* When '$' is followed by a whitespace, insert current value */
    if (isspace(ch)) {
        ptr --; /* Give back whitespace */
        corto_t_addVar(t, NULL, 0);

    } else if (ch == CORTO_T_OPEN) {
        ptr = corto_t_skipspace(ptr + 1);

        char *end = corto_t_id(t, ptr);
        if (!end) {
            goto error;
        }

        corto_t_addVar(t, ptr, 1 + end - ptr);

        ptr = corto_t_skipspace(end + 1);
        if (*ptr != CORTO_T_CLOSE) {
            corto_t_err(t, "mismatched '{'", start);
            goto error;
        }

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

static void corto_t_print(corto_t *t) {
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

corto_t* corto_t_compile(corto_string template) {
    char *ptr, ch;

    corto_t *t = corto_calloc(sizeof(corto_t));
    t->template = corto_strdup(template);
    t->current = &t->ops;

    for (ptr = template; (ch = *ptr); ptr ++) {
        switch(ch) {
        case CORTO_T_SIGIL:
            ptr = corto_t_section(t, ptr);
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

    corto_t_print(t);

    return t;
error:
    return NULL;
}
