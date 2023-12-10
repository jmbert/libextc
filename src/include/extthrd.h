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

#ifndef _EXT_THRD_H
#define _EXT_THRD_H

#include <extcdecl.h>
#include <sched.h>
#include <compiler.h>

enum _extthrderr
{
	E_ATTRNULL = 1,
	E_MMAPFAIL,
};

/*
	TODO: Get these properly, instead of just setting to constant
*/
#define THREADS_MAX 250000
#define THREAD_STACK_SIZE 0x10000


typedef pid_t exttid_t;

enum _t_states
{
	T_RUNNING,
	T_EXITED,
	T_ZOMBIE,
	T_JOINED,
};

typedef struct
{
	exttid_t _tid;
	unsigned long _flags;

	unsigned int _state;
	void *_ret;

	void *stack;
	unsigned long stacksize;
}exttattr_t;

extern exttattr_t *_threads[THREADS_MAX];
extern pid_t group_pid;

#define _THREAD_INDEX(_tid) (_tid-group_pid)
#define _GET_THREAD_ATTR(_tid) (_threads[_THREAD_INDEX(_tid)])
#define _IS_RUNNING(_tid) (_GET_THREAD_ATTR(_tid)->_state == T_RUNNING)

BEGIN_EXTCDECL

__init void __threads_init();

int spawn_thread(exttattr_t *attr, int(*fn)());

__noreturn void exit_thread(void *_retval);
exttid_t gettid();

END_EXTCDECL

#endif