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


CORTO_T_STD_EXPORT corto_void _corto_t_std_each(
    corto_string arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_each(arg, block, chainArg, ctx) _corto_t_std_each(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_bool _corto_t_std_elif(
    corto_string arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_elif(arg, block, chainArg, ctx) _corto_t_std_elif(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_void _corto_t_std_else(
    corto_string arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_else(arg, block, chainArg, ctx) _corto_t_std_else(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_string _corto_t_std_id(
    corto_string arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_id(arg, block, chainArg, ctx) _corto_t_std_id(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_bool _corto_t_std_if(
    corto_string arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_if(arg, block, chainArg, ctx) _corto_t_std_if(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_bool _corto_t_std_ifn(
    corto_string arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_ifn(arg, block, chainArg, ctx) _corto_t_std_ifn(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_string _corto_t_std_name(
    corto_string arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_name(arg, block, chainArg, ctx) _corto_t_std_name(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_object _corto_t_std_parent(
    corto_string arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_parent(arg, block, chainArg, ctx) _corto_t_std_parent(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_void _corto_t_std_scope(
    corto_string arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_scope(arg, block, chainArg, ctx) _corto_t_std_scope(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_type _corto_t_std_type(
    corto_string arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_type(arg, block, chainArg, ctx) _corto_t_std_type(arg, block, chainArg, ctx)

#ifdef __cplusplus
}
#endif
#endif

