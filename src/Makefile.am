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

ACLOCAL_AMFLAGS= -I m4

LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status libtool

SUBDIRS=channel

lib_LTLIBRARIES=libextc.la
libextc_la_SOURCES=libextc.c
libextc_la_LIBADD= channel/libChannel.a
include_HEADERS= \
	include/extchannel.h\
	include/extcdecl.h\
	include/extco.h\
	include/asm-port.h\
	include/compiler.h