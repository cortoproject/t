/* t.h
 *
 * This file contains generated code. Do not modify!
 */

#ifndef CORTO_T_H
#define CORTO_T_H

#include <corto/corto.h>
#include <corto/t/_interface.h>
/* $header() */

#define CORTO_T_SIGIL '$'
#define CORTO_T_OPEN '{'
#define CORTO_T_CLOSE '}'
#define CORTO_T_OP_BUFF_COUNT (64)
#define CORTO_T_IMPORT_BUFF_COUNT (8)
#define CORTO_T_FUNCTION_DEPTH (16)

typedef struct corto_t corto_t;

typedef struct corto_t_var {
    corto_string key;
    corto_value value;
} corto_t_var;

typedef struct corto_t_context {
    corto_t_var* (*findvar)(corto_string key, void *data);
    void *data;
} corto_t_context;

typedef struct corto_t_block corto_t_block;

/* Front end template functions */
CORTO_T_EXPORT corto_t* corto_t_compile(corto_string template);
CORTO_T_EXPORT void corto_t_free(corto_t *t);
CORTO_T_EXPORT corto_string corto_t_run(corto_t *t, corto_t_context *ctx);

/* Back end template functions */
CORTO_T_EXPORT corto_int16 corto_t_block_run(
    corto_t_block *b,
    corto_word ctx);

CORTO_T_EXPORT corto_t_var* corto_t_findvar(corto_string var, corto_word ctx);

/* Debug functions */
CORTO_T_EXPORT void corto_t_print(corto_t *t);

/* $end */

#include <corto/t/_type.h>
#include <corto/t/_api.h>
#include <corto/t/_meta.h>


#ifdef __cplusplus
extern "C" {
#endif

#include <corto/t/function.h>

#ifdef __cplusplus
}
#endif
#endif

