#include "async/Thread.h"
#include <sdl.h>

namespace async
{
	void Thread::sleep( float seconds )
	{
		SDL_Delay( static_cast< uint32_t >( seconds * 1000.0f ) );
	}
}