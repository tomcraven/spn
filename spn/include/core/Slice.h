#ifndef CORE_SLICE_H
#define CORE_SLICE_H

#include "core/Types.h"

namespace core
{
	template< class T >
	class Slice
	{
	public:
		Slice( T ptr, uint32_t size ) : data( ptr ), dataSize( size )
		{
		}

		uint32_t size()
		{
			return dataSize;
		}

		T ptr()
		{
			return data;
		}

	private:
		T data;
		uint32_t dataSize;
	};
}

#endif