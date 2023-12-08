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

#ifndef _EXT_CDECL_H
#define _EXT_CDECL_H

#ifdef BEGIN_EXTCDECL
	#undef BEGIN_EXTCDECL
#endif
#ifdef END_EXTCDECL
	#undef END_EXTCDECL
#endif

#ifdef __cplusplus
	#define BEGIN_EXTCDECL extern "C" {
	#define END_EXTCDECL }
#else
	#define BEGIN_EXTCDECL
	#define END_EXTCDECL
#endif

#endif