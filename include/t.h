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

/* Number of operations in a buffer */
#define CORTO_T_OP_BUFF_COUNT (64)

/* Number of imports in a buffer */
#define CORTO_T_IMPORT_BUFF_COUNT (8)

/* Number of variables in a buffer */
#define CORTO_T_VAL_BUFF_COUNT (16)

/* Maximum nesting depth for frames */
#define CORTO_T_FRAME_DEPTH (16)

/* Maximum number of arguments for filter */
#define CORTO_T_MAX_ARGS (16)

typedef struct corto_t corto_t;

typedef struct corto_t_var {
    corto_string key;
    corto_value value;
} corto_t_var;

typedef struct corto_t_frame {
    corto_t_var* (*findvar)(corto_string key, void *data);
    void *data;
} corto_t_frame;

typedef struct corto_t_block corto_t_block;

/* Front end template functions */
CORTO_T_EXPORT corto_t* corto_t_compile(corto_string template);
CORTO_T_EXPORT void corto_t_free(corto_t *t);
CORTO_T_EXPORT corto_string corto_t_run(corto_t *t, corto_t_frame *globals);

/* Back end template functions */
CORTO_T_EXPORT corto_int16 corto_t_block_run(
    corto_t_block *b,
    corto_word ctx);
CORTO_T_EXPORT corto_t_var* corto_t_findvar(corto_string var, corto_word ctx);
CORTO_T_EXPORT corto_int16 corto_t_pushframe(corto_t_frame *frame, corto_word ctx);
CORTO_T_EXPORT void corto_t_popframe(corto_word ctx);

/* Convenience function to find a default variable (to be used in a frame) */
CORTO_T_EXPORT corto_t_var* corto_t_finddefault(corto_string var, void *data);

/* Debug functions */
CORTO_T_EXPORT void corto_t_print(corto_t *t);

/* $end */

#include <corto/t/_type.h>
#include <corto/t/_api.h>
#include <corto/t/_meta.h>


#ifdef __cplusplus
extern "C" {
#endif

#include <corto/t/comparator.h>
#include <corto/t/function.h>

#ifdef __cplusplus
}
#endif
#endif

