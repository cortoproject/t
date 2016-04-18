/* t.h
 *
 * This file is generated. Do not modify.
 */

#ifndef CORTO_T_H
#define CORTO_T_H

#include "corto/corto.h"

#ifdef __cplusplus
extern "C" {
#endif

/* $header() */

#define CORTO_T_SIGIL '$'
#define CORTO_T_OPEN '{'
#define CORTO_T_CLOSE '}'
#define CORTO_T_OP_BUFF_COUNT (64)

typedef struct corto_t corto_t;

typedef struct corto_t_var {
    corto_string key;
    void *value;
    corto_type type;
} corto_t_var;

typedef struct corto_t_context {
    corto_t_var* (*findvar)(corto_string key, void *data);
    void *data;
} corto_t_context;

/* Low level template functions */
corto_t* corto_t_compile(corto_string template);
corto_string corto_t_run(corto_t *t, corto_t_context *ctx);

/* $end */

#ifdef __cplusplus
}
#endif
#endif
