#include "core/Time.h"
#include "core/Assert.h"
#include <sdl.h>

namespace core
{
	bool Time::getMilliseconds( uint64_t &outMilliseconds )
	{
		outMilliseconds = SDL_GetTicks();
		return true;
	}

	bool Time::getSeconds( float &outSeconds )
	{
		outSeconds = static_cast< float >( SDL_GetTicks() );
		outSeconds /= 1000.0f;
		return true;
	}
}