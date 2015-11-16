#ifndef CORE_PLATFORM_H
#define CORE_PLATFORM_H

#include <stdio.h>
#include <string.h>

#define SPRINTF( buffer, size, format, ... ) snprintf( buffer, size, format, ##__VA_ARGS__ )

#define STRTOK_S( str, delim, context ) strtok_r( str, delim, context )

#define SSCANF_S( str, format, ... ) sscanf( str, format, ##__VA_ARGS__ )

#endif