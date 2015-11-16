#ifndef CORE_FILE_H
#define CORE_FILE_H

struct s3eFile;

#include "core/Slice.h"

namespace core
{
	class File
	{
	public:
		bool openRead( const char* path );
		uint32_t size();

		template< class T >
		bool read( core::Slice< T >& slice )
		{
			return true;
		}

	private:
		s3eFile* fileHandle;
		uint32_t fileSize;
	};
}

#endif