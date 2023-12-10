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

#ifndef __EXT_COMPILER_H
#define __EXT_COMPILER_H

#define __attr(_attr) [[_attr]]

#define __gcc_attr(_attr) __attribute__((_attr))
#define __packed __gcc_attr(packed)
#define __constructor __gcc_attr(constructor)
#define __init __constructor

#define __noreturn __attr(noreturn)

#endif