
#include "corto/t/t.h"
#include "intern.h"

typedef struct corto_t_run_t {
    corto_t *t;
    corto_buffer buf;
    corto_t_context *ctx;
    corto_t_opbuff *current;
    corto_uint32 op;
} corto_t_run_t;

static void corto_t_runop(corto_t_op *op, corto_t_run_t *data);

corto_int16 corto_t_run_ops(
    corto_int32 length,
    corto_t_run_t *data)
{
    corto_uint32 count = 0;
    do {
        while ((data->op < data->current->opCount) && ((length < 0) || (count < length))) {
            corto_t_op *op = &data->current->ops[data->op];
            corto_t_runop(op, data);
            data->op ++;
            count ++;
        }
        data->op = 0;
    } while ((data->current = data->current->next));

    return 0;
}

corto_int16 corto_t_block_run(
    corto_t *t,
    corto_t_block *b,
    corto_buffer *buffer,
    corto_t_context *ctx)
{
    corto_t_run_t data = {t, *buffer, ctx, b->ops, b->start};

    corto_t_run_ops(b->length, &data);

    *buffer = data.buf;

    return 0;
}

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
        } else {
            corto_buffer_appendstr(&data->buf, "");
        }
        break;
    }
    }
}

corto_string corto_t_run(corto_t *t, corto_t_context *ctx) {
    corto_t_run_t data = {t, CORTO_BUFFER_INIT, ctx, &t->ops, 0};

    corto_t_run_ops(-1, &data);

    return corto_buffer_str(&data.buf);
}
