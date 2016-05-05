
#include "corto/t/t.h"
#include "intern.h"

typedef struct corto_t_run_t {
    corto_t *t;
    corto_buffer buf;
    corto_t_context *ctx;
    corto_t_opbuff *current;
    corto_uint32 op;

    /* After executing a block, current and op jump back to their previous
     * positions. These members cache the values before restoring current and op
     * so that a program can efficiently jump to the end of a block if required.
     */
    corto_t_opbuff *prevCurrent;
    corto_uint32 prevOp;
} corto_t_run_t;

static corto_bool corto_t_runop(corto_t_op *op, corto_t_run_t *data);

corto_int16 corto_t_run_ops(
    corto_t_opbuff *untilBuff,
    corto_uint32 untilOp,
    corto_t_run_t *data)
{
    do {
        while ((data->op < data->current->count) &&
               (!untilBuff || ((data->current != untilBuff) ||
                               (data->op != untilOp))))
        {
            corto_t_op *op = &data->current->ops[data->op];
            if (!corto_t_runop(op, data)) {
                data->op ++;
            }
        }
        data->op = 0;
    } while ((data->current = data->current->next));

    return 0;
}

static void corto_t_block_jump(
    corto_t_block *b,
    corto_t_run_t *data)
{
    data->current = b->stopBuff;
    data->op = b->stopOp;
}

corto_int16 corto_t_block_run(
    corto_t_block *b,
    corto_word ctx)
{
    corto_t_run_t *data = (corto_t_run_t*)ctx;
    corto_t_opbuff *current = data->current;
    corto_uint32 op = data->op;

    data->current = b->startBuff;
    data->op = b->startOp;
    corto_int16 result = corto_t_run_ops(b->stopBuff, b->stopOp, data);

    /* Restore position */
    data->current = current;
    data->op = op;

    return result;
}

/* Returns TRUE if operation manually set the program counter */
static corto_bool corto_t_runop(corto_t_op *op, corto_t_run_t *data) {
    corto_bool jumped = FALSE;

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
            void *value = corto_value_getPtr(&v->value);
            if (corto_instanceof(corto_text_o, corto_value_getType(&v->value))) {
                corto_buffer_appendstr(&data->buf, *(corto_string*)value);
            } else {
                corto_string str = corto_strv(&v->value, 0);
                corto_buffer_appendstr(&data->buf, str);
                corto_dealloc(str);
            }
        } else {
            corto_buffer_appendstr(&data->buf, "");
        }
        break;
    }

    case CORTO_T_FUNCTION: {
        corto_t_function f = op->data.function.function;
        corto_type returnType = corto_function(f)->returnType;
        corto_id arg;
        void *result = NULL;

        /* Allocate temporary memory for function returnvalue on stack */
        if (returnType && (returnType->kind != CORTO_VOID)) {
            if (corto_function(f)->returnsReference) {
                result = alloca(sizeof(corto_object));
            } else {
                result = alloca(corto_type_sizeof(returnType));
            }
        }

        corto_t_copySliceToString(arg, op->data.function.arg);

        /* Invoke function */
        corto_call(
            corto_function(f),
            result,
            arg,
            f->requiresBlock ? &op->data.function.block : NULL,
            data);

        /* Append returnvalue of function to buffer */
        if (returnType) {
            if (corto_instanceof(corto_text_o, returnType)) {
                if (*(corto_string*)result) {
                    corto_buffer_appendstr(&data->buf, *(corto_string*)result);
                    corto_dealloc(*(corto_string*)result);
                } else {
                    corto_buffer_appendstr(&data->buf, "");
                }
            } else {
                corto_string str = corto_strp(result, returnType, 0);
                if (str) {
                    corto_buffer_appendstr(&data->buf, str);
                    corto_dealloc(str);
                } else {
                    corto_buffer_appendstr(&data->buf, "");
                }
            }
        }

        if (f->requiresBlock) {
            corto_t_block_jump(&op->data.function.block, data);
            jumped = TRUE;
        }

        break;
    }
    }

    return jumped;
}

corto_string corto_t_run(corto_t *t, corto_t_context *ctx) {
    corto_t_run_t data = {t, CORTO_BUFFER_INIT, ctx, &t->ops, 0};

    corto_t_run_ops(NULL, 0, &data);

    return corto_buffer_str(&data.buf);
}

corto_t_var* corto_t_findvar(corto_string var, corto_word ctx) {
    corto_t_run_t *data = (corto_t_run_t*)ctx;
    return data->ctx->findvar(var, data->ctx->data);
}
