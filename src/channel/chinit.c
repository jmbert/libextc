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

#include <extchannel.h>
#include <stdlib.h>
#include <errno.h>

int chinit(channel_t *ch, unsigned int size, unsigned int nmemb)
{
	if (!ch)
	{
		return -E_CHNULL;
	}
	ch->_chnmemb = nmemb;
	ch->_chsize = size;
	ch->_chbase = malloc(size*nmemb);
	unsigned int _save_errno = errno;
	if (!ch->_chbase)
	{
		return -E_CHNOMALLOC;
	}
	ch->_chinto = ch->_chbase;
	return 0;
}