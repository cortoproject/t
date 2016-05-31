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


CORTO_T_STD_EXPORT corto_int64 _corto_t_std_abs(
    corto_int64 arg);
#define corto_t_std_abs(arg) _corto_t_std_abs(arg)

CORTO_T_STD_EXPORT corto_uint64 _corto_t_std_count(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_count(arg, block, chainArg, ctx) _corto_t_std_count(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_bool _corto_t_std_declared(
    corto_value* arg1,
    corto_value* arg2,
    corto_word ctx);
#define corto_t_std_declared(arg1, arg2, ctx) _corto_t_std_declared(arg1, arg2, ctx)

CORTO_T_STD_EXPORT corto_bool _corto_t_std_defined(
    corto_value* arg1,
    corto_value* arg2,
    corto_word ctx);
#define corto_t_std_defined(arg1, arg2, ctx) _corto_t_std_defined(arg1, arg2, ctx)

CORTO_T_STD_EXPORT corto_void _corto_t_std_each(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_each(arg, block, chainArg, ctx) _corto_t_std_each(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_bool _corto_t_std_elif(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_elif(arg, block, chainArg, ctx) _corto_t_std_elif(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_bool _corto_t_std_elifn(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_elifn(arg, block, chainArg, ctx) _corto_t_std_elifn(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_void _corto_t_std_else(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_else(arg, block, chainArg, ctx) _corto_t_std_else(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_string _corto_t_std_id(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_id(arg, block, chainArg, ctx) _corto_t_std_id(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_bool _corto_t_std_if(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_if(arg, block, chainArg, ctx) _corto_t_std_if(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_bool _corto_t_std_ifn(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_ifn(arg, block, chainArg, ctx) _corto_t_std_ifn(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_bool _corto_t_std_instanceof(
    corto_value* arg1,
    corto_value* arg2,
    corto_word ctx);
#define corto_t_std_instanceof(arg1, arg2, ctx) _corto_t_std_instanceof(arg1, arg2, ctx)

CORTO_T_STD_EXPORT corto_string _corto_t_std_lower(
    corto_string arg);
#define corto_t_std_lower(arg) _corto_t_std_lower(arg)

CORTO_T_STD_EXPORT corto_string _corto_t_std_name(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_name(arg, block, chainArg, ctx) _corto_t_std_name(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_bool _corto_t_std_observable(
    corto_value* arg1,
    corto_value* arg2,
    corto_word ctx);
#define corto_t_std_observable(arg1, arg2, ctx) _corto_t_std_observable(arg1, arg2, ctx)

CORTO_T_STD_EXPORT corto_object _corto_t_std_parent(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_parent(arg, block, chainArg, ctx) _corto_t_std_parent(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_bool _corto_t_std_persistent(
    corto_value* arg1,
    corto_value* arg2,
    corto_word ctx);
#define corto_t_std_persistent(arg1, arg2, ctx) _corto_t_std_persistent(arg1, arg2, ctx)

CORTO_T_STD_EXPORT corto_float64 _corto_t_std_pow(
    corto_float64 base,
    corto_float64 exponent);
#define corto_t_std_pow(base, exponent) _corto_t_std_pow(base, exponent)

CORTO_T_STD_EXPORT corto_void _corto_t_std_scope(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_scope(arg, block, chainArg, ctx) _corto_t_std_scope(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_bool _corto_t_std_scoped(
    corto_value* arg1,
    corto_value* arg2,
    corto_word ctx);
#define corto_t_std_scoped(arg1, arg2, ctx) _corto_t_std_scoped(arg1, arg2, ctx)

CORTO_T_STD_EXPORT corto_uint64 _corto_t_std_toint(
    corto_float64 arg);
#define corto_t_std_toint(arg) _corto_t_std_toint(arg)

CORTO_T_STD_EXPORT corto_type _corto_t_std_type(
    corto_value* arg,
    corto_t_block* block,
    corto_value* chainArg,
    corto_word ctx);
#define corto_t_std_type(arg, block, chainArg, ctx) _corto_t_std_type(arg, block, chainArg, ctx)

CORTO_T_STD_EXPORT corto_string _corto_t_std_upper(
    corto_string arg);
#define corto_t_std_upper(arg) _corto_t_std_upper(arg)

CORTO_T_STD_EXPORT corto_bool _corto_t_std_valid(
    corto_value* arg1,
    corto_value* arg2,
    corto_word ctx);
#define corto_t_std_valid(arg1, arg2, ctx) _corto_t_std_valid(arg1, arg2, ctx)

#ifdef __cplusplus
}
#endif
#endif

