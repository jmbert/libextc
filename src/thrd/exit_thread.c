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
#include <compiler.h>
#include <extpanic.h>
#include <sys/mman.h>
#include <errno.h>

#define __panic_fail_exit_thread(_msg, _args...)\
{\
	_PANIC("Failed to exit thread, exiting process: %s\n", _msg __VA_OPT__(,) _args);\
}\

int __threads_left()
{
	int threads = 0;
	for (unsigned int i = 0; i < THREADS_MAX; i++)
	{
		if (_threads[i])
		{	
			threads += (_threads[i]->_state == T_RUNNING);
		}
	}
	return threads;
}

__noreturn void _thread_zombie_idle(void (*done_handler)())
{
	for (;;)
	{
		if (done_handler)
		{
			if (!__threads_left())
			{
				done_handler();
			}
		}
	}

	__builtin_unreachable();
}

void __threads_done()
{
	exit(0);
}

__noreturn void exit_thread(void *_retval)
{
	exttattr_t *attrs = _GET_THREAD_ATTR(gettid());
	if (_THREAD_INDEX(gettid()) == 0)
	{
		_thread_zombie_idle(__threads_done);
	}
	if (attrs == NULL)
	{
		__panic_fail_exit_thread("Process has no associated attributes");
	}
	if (!_IS_RUNNING(gettid()))
	{
		__panic_fail_exit_thread("Process not running");
	}
	attrs->_ret = _retval;
	attrs->_state = T_ZOMBIE;

	if (!__threads_left())
	{
		exit(0);
	}

	_thread_zombie_idle(NULL);

}