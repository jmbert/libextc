#ifndef _EXT_PANIC_H
#define _EXT_PANIC_H

#include <stdio.h>
#include <stdlib.h>

#define _PANIC_CODE 0xAA

#define _ERR_LOG stderr

#define _LOG_ERR(_msg, __args...) fprintf(_ERR_LOG, _msg __VA_OPT__(,) __args)

#define _PANIC(_msg, __args...) _LOG_ERR(_msg  __VA_OPT__(,) __args);exit(_PANIC_CODE)

#endif