/***
    extlibc - C library extension
    Copyright (C) 2023  jmbert

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.]
***/

#ifndef _EXT_COROUTINE_H
#define _EXT_COROUTINE_H

#include <extcdecl.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <asm-port.h>

#define _COROUTINE_RESUME(_return) _return (*_resume)()

#define _CRT_MANGLE(_base, _name) _base ## _ ## _name

#define crt_new(_name, _return) \
	struct _CRT_MANGLE(__coroutine, _name) \
	{ \
		_COROUTINE_RESUME(_return);\
		void *_sf;\
		unsigned int _sfsize;\
	}_CRT_MANGLE(_crt, _name)\


#define crt_setup(_name) \
	uintptr_t rsp;\
	uintptr_t rbp\

/*
	The meat of the coroutine system (very evil)
	Here we jump over the actual yield, only to call back to it
	This callback pushes the resume rip onto the stack
	We then pop it into the resume address, and return
*/
#define crt_yield(_value, _name) \
	{\
	__label__ yield, save_pc;\
	goto save_pc;\
yield:\
	__asm__ volatile (\
		ASM_POP(%0)\
		ASM_MOV(%%rsp, %1)\
		ASM_MOV(%%rbp, %2)\
		: "=m"(_CRT_MANGLE(_crt, _name)._resume), "=m"(rsp), "=m"(rbp)\
	);\
	_CRT_MANGLE(_crt, _name)._sfsize = rbp-rsp;\
	if (_CRT_MANGLE(_crt, _name)._sf) {free(_CRT_MANGLE(_crt, _name)._sf);} \
	_CRT_MANGLE(_crt, _name)._sf = malloc(_CRT_MANGLE(_crt, _name)._sfsize);\
	memcpy(_CRT_MANGLE(_crt, _name)._sf, (void*)rsp, _CRT_MANGLE(_crt, _name)._sfsize);\
	return _value;\
save_pc:\
	__asm__ goto (\
		ASM_CALL(%l0)\
		: : : :\
		yield\
	);\
	__asm__ volatile (\
		ASM_PUSH(%%rbp)\
		ASM_MOV(%%rsp, %%rbp)\
		ASM_SUB(%2, %%rsp)\
		ASM_MOV(%%rsp, %0)\
		ASM_MOV(%%rbp, %1)\
		:  "=m"(rsp), "=m"(rbp)\
		: "m"(_CRT_MANGLE(_crt, _name)._sfsize));\
	memcpy((void*)rsp, _CRT_MANGLE(_crt, _name)._sf, _CRT_MANGLE(_crt, _name)._sfsize);\
	}\

#define crt_init(_name) _CRT_MANGLE(_crt, _name)._sf = NULL;_CRT_MANGLE(_crt, _name)._resume = NULL

#define crt_resume(_name) _CRT_MANGLE(_crt, _name)._resume()

BEGIN_EXTCDECL

END_EXTCDECL

#endif