#ifndef CORE_FILE_H
#define CORE_FILE_H

#include "core/Slice.h"

#include <sdl.h>

namespace core
{
	class File
	{
	public:
		bool openRead( const char* filename );
		uint32_t size();

		template< class T >
		uint32_t read( core::Slice< T >& slice )
		{
			SDL_RWread( fileHandle, slice.ptr(), sizeof( uint8_t ), slice.size() );

			return 0;
		}

	private:
		SDL_RWops* fileHandle;
	};
}

#endif