
#include "corto/t/t.h"
#include "intern.h"

typedef struct corto_t_varbuff {
    corto_t_var vars[CORTO_T_VAL_BUFF_COUNT];
    corto_uint32 count;
    struct corto_t_varbuff *next;
} corto_t_varbuff;

typedef struct corto_t_run_t {
    corto_t *t;
    corto_buffer buf;
    corto_t_frame *globals;
    corto_t_frame *stack[CORTO_T_FRAME_DEPTH];
    corto_value lastResult; /* For chaining functions */
    corto_bool reg; /* For storing comparator result */
    corto_uint32 sp;
    corto_t_opbuff *current;
    corto_uint32 op;
    corto_t_varbuff vars;
} corto_t_run_t;

static corto_bool corto_t_runop(corto_t_op *op, corto_t_run_t *data);

/* Run a number of operations until specified operation is encountered */
static corto_int16 corto_t_run_ops(
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

/* Skip over a block */
static void corto_t_block_jump(
    corto_t_block *b,
    corto_t_run_t *data)
{
    data->current = b->stopBuff;
    data->op = b->stopOp;
}

/* Run a single code block */
corto_int16 corto_t_block_run(
    corto_t_block *b,
    corto_word ctx)
{
    corto_t_run_t *data = (corto_t_run_t*)ctx;

    /* Cache current position and set op buffer and pc to block */
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

static corto_int16 corto_t_parseMember(corto_value *value, corto_t_slice mbr) {
    corto_id memberName;
    char *ptr = mbr.ptr, *bptr, ch;
    corto_member member;


    do {
        corto_type t = corto_value_getType(value);
        void *vptr = corto_value_getPtr(value);

        bptr = memberName;

        for (ptr = ptr + 1; ((ch = *ptr) != '.') && ((ptr - mbr.ptr) < mbr.len); ptr++) {
            *bptr = ch;
            bptr++;
        }
        *bptr = '\0';

        /* Report error after parsing memberName for more meaningful error */
        if (!corto_instanceof(corto_interface_o, t)) {
            corto_seterr(
              "can't resolve member '%s' from value of non-composite type '%s'",
              memberName,
              corto_fullpath(NULL, t));
            goto error;
        }

        member = corto_interface_resolveMember(t, memberName);
        if (!member) {
            corto_seterr("unresolved member '%s' in type '%s'",
                memberName,
                corto_fullpath(NULL, t));
            goto error;
        }

        *value = corto_value_value(member->type, CORTO_OFFSET(vptr, member->offset));
    } while ((ptr - mbr.ptr) < mbr.len);

    return 0;
error:
    return -1;
}

static corto_value* corto_t_parseExpr(
    corto_t_expr *expr,
    corto_value *arg,
    corto_t_run_t *data)
{
    corto_value *result = NULL;
    corto_id argId;
    corto_t_exprKind kind = expr->kind;
    corto_t_slice member = {NULL, 0};

    switch(kind) {
    case CORTO_T_IDENTIFIER_MEMBER: {
        corto_t_slice idNoMembers = {
          expr->expr.identifier_member.identifier.ptr,
          expr->expr.identifier_member.idLen
        };
        corto_t_copySliceToString(argId, idNoMembers);

        /* Get slice containing just the member expression (from . onwards) */
        member = (corto_t_slice){
          expr->expr.identifier_member.identifier.ptr + expr->expr.identifier_member.idLen,
          expr->expr.identifier_member.identifier.len - expr->expr.identifier_member.idLen
        };
    }

    case CORTO_T_IDENTIFIER: {
        if (expr->kind == CORTO_T_IDENTIFIER) {
            corto_t_copySliceToString(argId, expr->expr.identifier);
        }
        corto_t_var *v = corto_t_findvar(argId, (corto_word)data);
        if (v) {
            if (expr->kind == CORTO_T_IDENTIFIER) {
                result = &v->value;
            } else {
                *arg = v->value;
                result = arg;
            }
        }
        break;
    }
    case CORTO_T_OBJECT_MEMBER:
        *arg = corto_value_object(expr->expr.object_member.object, NULL);
        member = (corto_t_slice){
            expr->expr.object_member.member.ptr,
            expr->expr.object_member.member.len
        };
        result = arg;
        break;
    case CORTO_T_OBJECT:
        *arg = corto_value_object(expr->expr.object, NULL);
        result = arg;
        break;
    case CORTO_T_LITERAL:
        *arg = corto_value_value(expr->expr.literal.type, &expr->expr.literal.value);
        result = arg;
        break;
    }

    if ((kind == CORTO_T_IDENTIFIER_MEMBER) || (kind == CORTO_T_OBJECT_MEMBER)) {
        if (result) {
            if (corto_t_parseMember(result, member)) {
                goto error;
            }
        }
    }

    return result;
error:
    return NULL;
}

static corto_bool corto_t_castValue(
    corto_value *v,
    corto_type type)
{
    corto_bool freeArg = FALSE;

    /* Cast argument if necessary (chainArg always matches type) */
    if (v) {
        corto_type vType = corto_value_getType(v);
        if (vType && type && (type != vType)) {
            /* For now only support primitive conversions */
            if ((vType->kind == CORTO_PRIMITIVE) && (type->kind == CORTO_PRIMITIVE)) {
                void *src = corto_value_getPtr(v);
                *v = corto_value_value(type, NULL);
                corto_convert(vType, src, type, &v->is.value.storage);
                v->is.value.v = &v->is.value.storage;
                if (corto_primitive(type)->kind == CORTO_TEXT) {
                    freeArg = TRUE;
                }
            }
        }
    }

    return freeArg;
}

static corto_bool corto_t_runFunction(corto_t_op *op, corto_bool comparator, corto_t_run_t *data) {
    corto_t_function f = op->data.function.function;
    corto_type returnType = corto_function(f)->returnType;
    corto_value *arg = NULL, argMem;
    corto_bool freeArg = FALSE;
    corto_bool jumped = FALSE;
    void *result = NULL;

    /* Allocate temporary memory for function returnvalue on stack */
    if (returnType && (returnType->kind != CORTO_VOID)) {
        if (corto_function(f)->returnsReference) {
            result = alloca(sizeof(corto_object));
        } else {
            result = alloca(corto_type_sizeof(returnType));
        }
    }

    /* Obtain argument value */
    if (!comparator) {
        arg = corto_t_parseExpr(&op->data.function.arg, &argMem, data);
    } else {
        /* If function has a comparator, result has been set in register */
        argMem = corto_value_value(corto_bool_o, &data->reg);
        arg = &argMem;
    }
    freeArg = corto_t_castValue(arg, f->argType);

    /* Invoke function */
    corto_call(
        corto_function(f),
        result,
        arg,
        f->requiresBlock ? &op->data.function.block : NULL,
        f->chain ? &data->lastResult : NULL,
        data);

    /* Free arg if casted */
    if (freeArg) {
        corto_string *str = corto_value_getPtr(arg);
        if (str && *str) {
            corto_dealloc(*str);
        }
    }

    /* Free last result */
    if (corto_value_getPtr(&data->lastResult)) {
        corto_type t = corto_value_getType(&data->lastResult);
        void *ptr = corto_value_getPtr(&data->lastResult);
        if (ptr) {
            if (t->kind == CORTO_PRIMITIVE) {
                if (corto_primitive(t)->kind == CORTO_TEXT) {
                    if (*(corto_string*)ptr) {
                        corto_dealloc(*(corto_string*)ptr);
                    }
                }
            } else if (t->reference) {
                if (*(corto_object*)ptr) {
                    corto_release(*(corto_object*)ptr);
                }
            } else {
                corto_deinitp(ptr, t);
                corto_dealloc(ptr);
            }
        }

        /* Reset lastResult */
        data->lastResult = corto_value_value(NULL, NULL);
    }

    if (returnType && op->data.function.keepResult) {
        void *ptr = NULL;
        data->lastResult = corto_value_value(returnType, NULL);

        /* Use 64-bit storage of value object to store scalar values */
        if ((returnType->kind == CORTO_PRIMITIVE) || returnType->reference) {
            ptr = &data->lastResult.is.value.storage;
            memcpy(ptr, result, corto_type_sizeof(returnType));

        /* Allocate on heap for non-scalar/reference values */
        } else {
            ptr = corto_calloc(corto_type_sizeof(returnType));
            corto_copyp(ptr, returnType, result);
        }

        data->lastResult.is.value.v = ptr;
    }

    /* Append returnvalue of function to buffer */
    if (returnType && corto_t_function(f)->echo) {
        if (corto_instanceof(corto_text_o, returnType)) {
            if (*(corto_string*)result) {
                corto_buffer_appendstr(&data->buf, *(corto_string*)result);
                if (!op->data.function.keepResult) {
                    corto_dealloc(*(corto_string*)result);
                }
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

    return jumped;
}

static void corto_t_runComparator(corto_t_op *op, corto_t_run_t *data) {
    corto_t_comparator c = op->data.comparator.comparator;
    corto_value *arg1 = NULL, *arg2 = NULL, argMem1, argMem2;
    corto_bool freeArg1 = FALSE, freeArg2 = FALSE;

    /* Obtain 1st argument value from function reference */
    arg1 = corto_t_parseExpr(
        &op->data.comparator.function->data.function.arg,
        &argMem1,
        data);
    freeArg1 = corto_t_castValue(arg1, c->argType);

    /* Parse 2nd argument */
    arg2 = corto_t_parseExpr(
        &op->data.comparator.arg,
        &argMem2,
        data);
    freeArg2 = corto_t_castValue(arg2, c->argType);

    /* Invoke function */
    corto_call(
        corto_function(c),
        &data->reg,
        arg1,
        arg2,
        data);

    /* Free args if casted */
    if (freeArg1) {
        corto_string *str = corto_value_getPtr(arg1);
        if (str && *str) {
            corto_dealloc(*str);
        }
    }
    if (freeArg2) {
        corto_string *str = corto_value_getPtr(arg2);
        if (str && *str) {
            corto_dealloc(*str);
        }
    }
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

    case CORTO_T_VAL: {
        corto_value valMem, *val = corto_t_parseExpr(
            &op->data.val.expr,
            &valMem,
            data);

        if (val) {
            void *ptr = corto_value_getPtr(val);
            if (corto_instanceof(corto_text_o, corto_value_getType(val))) {
                corto_buffer_appendstr(&data->buf, *(corto_string*)ptr);
            } else {
                corto_string str = corto_strv(val, 0);
                corto_buffer_appendstr(&data->buf, str);
                corto_dealloc(str);
            }
        } else {
            corto_buffer_appendstr(&data->buf, "");
        }
        break;
    }

    case CORTO_T_FUNCTION:
        jumped = corto_t_runFunction(op, FALSE, data);
        break;

    case CORTO_T_FUNCTION_COMPARATOR:
        jumped = corto_t_runFunction(op, TRUE, data);
        break;

    case CORTO_T_COMPARATOR:
        corto_t_runComparator(op, data);
        break;
    }

    return jumped;
}

corto_string corto_t_run(corto_t *t, corto_t_frame *globals) {
    corto_string result = NULL;
    corto_t_run_t data = {t, CORTO_BUFFER_INIT, globals, {NULL}, {0}, 0, 0, &t->ops, 0};
    data.vars.count = 0;
    data.vars.next = 0;
    data.lastResult = corto_value_value(NULL, NULL);

    corto_t_run_ops(NULL, 0, &data);

    /* Never return NULL */
    if (!(result = corto_buffer_str(&data.buf))) {
        result = corto_strdup("");
    }

    return result;
}

corto_t_var* corto_t_findvar(corto_string var, corto_word ctx) {
    corto_t_run_t *data = (corto_t_run_t*)ctx;
    corto_t_var *result = NULL;

    if (data->sp) {
        do {
            corto_t_frame *stack = data->stack[data->sp - 1];
            result = stack->findvar(var, stack->data);
        } while (!result && --data->sp);
    }

    if (!result) {
        result = data->globals->findvar(var, data->globals->data);
    }

    return result;
}

corto_int16 corto_t_pushframe(corto_t_frame *frame, corto_word ctx) {
    corto_t_run_t *data = (corto_t_run_t*)ctx;
    if (data->sp == CORTO_T_FRAME_DEPTH) {
        corto_seterr("maximum number of frames exceeded");
        goto error;
    }
    data->stack[data->sp ++] = frame;

    return 0;
error:
    return -1;
}

void corto_t_popframe(corto_word ctx) {
    corto_t_run_t *data = (corto_t_run_t*)ctx;
    data->sp --;
}

corto_t_var* corto_t_finddefault(corto_string var, void *data) {
    if (!var || !strlen(var) || !strcmp(var, ".")) {
        return (corto_t_var*)data;
    } else {
        return NULL;
    }
}
