#ifndef CORE_PLATFORM_H
#define CORE_PLATFORM_H

#include <stdio.h>

#define SPRINTF( buffer, size, format, ... ) sprintf_s( buffer, size, format, ##__VA_ARGS__ )

#endif