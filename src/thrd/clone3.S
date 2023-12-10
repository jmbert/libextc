#include <sys/syscall.h>

.extern foo2

.extern exit

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
	call exit

.reterr:
	mov -1, %rax
	ret