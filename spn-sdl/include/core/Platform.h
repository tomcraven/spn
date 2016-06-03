#ifndef CORE_PLATFORM_H
#define CORE_PLATFORM_H

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

// This ifdef check is incorrect, we should be building platform specific versions of this platform file
// Or is there an SDL version we could use? probably
#ifdef WINDOWS
#define SPRINTF( buffer, size, format, ... ) sprintf_s( buffer, size, format, ##__VA_ARGS__ )
#else
#define SPRINTF( buffer, size, format, ... ) sprintf( buffer, format, ##__VA_ARGS__ )
#endif

#endif
