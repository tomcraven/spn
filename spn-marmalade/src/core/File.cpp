#include "core/File.h"
#include "core/Assert.h"

#include "s3eFile.h"

namespace core
{
	bool File::openRead( const char* path )
	{
		fileHandle = s3eFileOpen( path, "r" );
		VALIDATE( fileHandle );

		int32_t size = s3eFileGetSize( fileHandle );
		VALIDATE( size >= 0 );

		fileSize = static_cast< uint32_t >( size );

		return true;
	}

	uint32_t File::size()
	{
		return fileSize;
	}
}