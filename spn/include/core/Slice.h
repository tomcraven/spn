#ifndef CORE_SLICE_H
#define CORE_SLICE_H

#include "core/Types.h"

namespace core
{
	template< class T >
	class Slice
	{
	public:
		Slice( T ptr, uint32_t size ) : data( reinterpret_cast< uint8_t* >( ptr ) ), dataSize( size )
		{
		}

		uint32_t size()
		{
			return dataSize;
		}

		T ptr()
		{
			return reinterpret_cast< T >( data );
		}

	private:
		uint8_t* data;
		uint32_t dataSize;
	};
}

#endif