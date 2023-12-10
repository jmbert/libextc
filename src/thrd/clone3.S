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

#include <sys/syscall.h>

.extern foo2

.extern exit_thread

.section .text
.global clone3
clone3:
	test %rdi, %rdi
	je .reterr
	test %rdx, %rdx
	je .reterr

	mov $SYS_clone3, %eax
	syscall

	test %rax, %rax
	jl .reterr
	jz .child

.ret:
	ret

.child:
	xor %rbp, %rbp

	call *%rdx
	mov %rax, %rdi
	call exit_thread

.reterr:
	mov -1, %rax
	ret