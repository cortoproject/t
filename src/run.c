
#include "corto/t/t.h"
#include "intern.h"

typedef struct corto_t_run_t {
    corto_t *t;
    corto_buffer buf;
    corto_t_context *ctx;
} corto_t_run_t;

static void corto_t_runop(corto_t_op *op, corto_t_run_t *data) {

    switch(op->kind) {
    case CORTO_T_TEXT: {
        corto_buffer_appendstrn(
            &data->buf,
            op->data.text.t.ptr,
            op->data.text.t.len);
        break;
    }

    case CORTO_T_VAR: {
        corto_id key;
        memcpy(key, op->data.var.key.ptr, op->data.var.key.len);
        key[op->data.var.key.len] = '\0';

        corto_t_var *v = data->ctx->findvar(key, data->ctx->data);
        if (v) {
            corto_buffer_appendstr(&data->buf, v->value);
        }
        break;
    }
    }
}

corto_string corto_t_run(corto_t *t, corto_t_context *ctx) {
    corto_t_opbuffer *current = &t->ops;
    corto_t_run_t data = {t, CORTO_BUFFER_INIT, ctx};

    do {
        corto_uint32 i = 0;
        while (i < current->opcount) {
            corto_t_op *op = &current->ops[i];
            corto_t_runop(op, &data);
            i ++;
        }
    } while ((current = current->next));

    return corto_buffer_str(&data.buf);
}
