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

#include <string.h>

int chreceive(channel_t *ch, void *buffer, unsigned int _nreceive)
{
	if (!ch)
	{
		return -E_CHNULL;
	}
	if (!ch->_chinto || !ch->_chbase || !buffer)
	{
		return -E_CHNULL;
	}
	if (!ch->_chsize || !ch->_chnmemb || !_nreceive)
	{
		return -E_CHNOSIZE;
	}
	ch->_chinto = ((char*)ch->_chinto) - _nreceive*ch->_chsize;
	if (ch->_chbase > ch->_chinto)
	{
		return -E_CHTOOMANY;
	}
	memcpy(buffer, ch->_chinto, _nreceive*ch->_chsize);

	return 0;
}