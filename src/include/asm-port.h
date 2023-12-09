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
#ifndef _ASM_H
#define _ASM_H

#if defined __x86_64__ || defined __ia64__

#define ASM_JUMP(_arg) 			"jmp " #_arg "\n"
#define ASM_CALL(_arg) 			"call " #_arg "\n"
#define ASM_SUB(_arg, _arg2) 	"sub " #_arg "," #_arg2 "\n"
#define ASM_MOV(_arg, _arg2) 	"mov " #_arg "," #_arg2 "\n"
#define ASM_POP(_arg)			"pop " #_arg "\n"
#define ASM_PUSH(_arg)			"push " #_arg "\n"

#else

#warning Inline assembly not ported to this architecture

#endif


#endif