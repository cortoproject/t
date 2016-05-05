/* std.h
 *
 * This file contains generated code. Do not modify!
 */

#ifndef CORTO_T_STD_H
#define CORTO_T_STD_H

#include <corto/corto.h>
#include <corto/t/std/_interface.h>
/* $header() */
/* You can put your own definitions here! */
/* $end */

#include <corto/t/std/_type.h>
#include <corto/t/std/_api.h>
#include <corto/t/std/_meta.h>

#include <corto/t/t.h>

#ifdef __cplusplus
extern "C" {
#endif


CORTO_T_STD_EXPORT corto_void _corto_t_std_else(
    corto_string arg,
    corto_t_block* block,
    corto_word ctx);
#define corto_t_std_else(arg, block, ctx) _corto_t_std_else(arg, block, ctx)

CORTO_T_STD_EXPORT corto_void _corto_t_std_foreach(
    corto_string arg,
    corto_t_block* block,
    corto_word ctx);
#define corto_t_std_foreach(arg, block, ctx) _corto_t_std_foreach(arg, block, ctx)

CORTO_T_STD_EXPORT corto_string _corto_t_std_id(
    corto_string arg,
    corto_t_block* block,
    corto_word ctx);
#define corto_t_std_id(arg, block, ctx) _corto_t_std_id(arg, block, ctx)

CORTO_T_STD_EXPORT corto_void _corto_t_std_if(
    corto_string arg,
    corto_t_block* block,
    corto_word ctx);
#define corto_t_std_if(arg, block, ctx) _corto_t_std_if(arg, block, ctx)

CORTO_T_STD_EXPORT corto_string _corto_t_std_name(
    corto_string arg,
    corto_t_block* block,
    corto_word ctx);
#define corto_t_std_name(arg, block, ctx) _corto_t_std_name(arg, block, ctx)

CORTO_T_STD_EXPORT corto_object _corto_t_std_parent(
    corto_string arg,
    corto_t_block* block,
    corto_word ctx);
#define corto_t_std_parent(arg, block, ctx) _corto_t_std_parent(arg, block, ctx)

CORTO_T_STD_EXPORT corto_void _corto_t_std_scope(
    corto_string arg,
    corto_t_block* block,
    corto_word ctx);
#define corto_t_std_scope(arg, block, ctx) _corto_t_std_scope(arg, block, ctx)

CORTO_T_STD_EXPORT corto_type _corto_t_std_type(
    corto_string arg,
    corto_t_block* block,
    corto_word ctx);
#define corto_t_std_type(arg, block, ctx) _corto_t_std_type(arg, block, ctx)

#ifdef __cplusplus
}
#endif
#endif

