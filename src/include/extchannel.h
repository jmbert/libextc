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

#ifndef _EXT_CHANNELS_H
#define _EXT_CHANNELS_H

#include <extcdecl.h>

enum cherrs
{
	E_CHNULL = 1,
	E_CHTOOMANY,
	E_CHNOSIZE,
	E_CHNOMALLOC,
};

typedef struct _channel
{
	void *_chinto;
	void *_chbase;
	unsigned int _chsize;
	unsigned int _chnmemb;
}channel_t;

BEGIN_EXTCDECL

int chinit(channel_t *ch, unsigned int size, unsigned int nmemb);
int chfree(channel_t *ch);
int chreceive(channel_t *ch, void *buffer, unsigned int _nreceive);
int chsend(channel_t *ch, void *buffer, unsigned int _nsend);

END_EXTCDECL

#endif