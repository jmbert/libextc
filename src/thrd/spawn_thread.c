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

#include <extthrd.h>
#include <errno.h>
#include <linux/sched.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdint.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <signal.h>

exttattr_t _threads[THREADS_MAX];

int clone_return;

extern long clone3(struct clone_args *args, size_t size, void(*fn_ptr)());

int spawn_thread(exttattr_t *attr, int(*fn)())
{
	if (!attr)
	{
		return -E_ATTRNULL;
	}
	struct clone_args *args = malloc(sizeof(*args));
	args->parent_tid = (uintptr_t)&(attr->_tid);
	args->flags = 
				CLONE_THREAD | CLONE_SIGHAND | CLONE_VM | 
				CLONE_PARENT_SETTID;

	args->stack = mmap(NULL, THREAD_STACK_SIZE, PROT_READ | PROT_WRITE,
						MAP_PRIVATE | MAP_ANONYMOUS |
						MAP_GROWSDOWN |
						MAP_STACK, -1, 0);

	if (args->stack == NULL)
	{
		return -E_MMAPFAIL;
	} /* So we don't immediatly segfault on a push */
	args->stack_size = THREAD_STACK_SIZE;

	attr->_flags = args->flags;
	long ret = clone3(args, sizeof(struct clone_args), fn);
	if (ret == -1)
	{
		return ret;
	}

	return 0;
}