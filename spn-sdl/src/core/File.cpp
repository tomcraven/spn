#include "core/File.h"
#include "core/Assert.h"

namespace core
{
	bool File::openRead( const char* filename )
	{
		fileHandle = SDL_RWFromFile( filename, "r" );
		VALIDATE( fileHandle );
		return true;
	}

	uint32_t File::size()
	{
		return static_cast< int32_t >( SDL_RWsize( fileHandle ) );
	}
}