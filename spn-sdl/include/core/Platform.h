#ifndef CORE_PLATFORM_H
#define CORE_PLATFORM_H

#include <stdio.h>
#include <iostream>

#define SPRINTF( buffer, size, format, ... ) sprintf_s( buffer, size, format, ##__VA_ARGS__ )

#define STRTOK_S( str, delim, context ) strtok_s( str, delim, context )

#define SSCANF_S( str, format, ... ) sscanf_s( str, format, ##__VA_ARGS__ )

#endif