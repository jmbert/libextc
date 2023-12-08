#
#    extlibc - C library extension
#    Copyright (C) 2023  jmbert
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.]
#

AC_INIT([libextc], [0.0.1])

AM_INIT_AUTOMAKE

LT_INIT(
	[shared]
	[disable-static]
)
AC_SUBST([LIBTOOL_DEPS])
AC_CONFIG_MACRO_DIRS(m4)
AC_CONFIG_FILES(
	[Makefile]
	[src/Makefile]
	[src/channel/Makefile]
)
AC_PROG_CC

AC_LANG([C])

AC_OUTPUT