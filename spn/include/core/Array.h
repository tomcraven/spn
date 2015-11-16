#ifndef CORE_ARRAY_H
#define CORE_ARRAY_H

#include "core/Assert.h"

namespace core
{
	template< class T >
	class Array
	{
	public:
		Array() : data( 0 ), numElements( 0 )
		{
		}

		~Array()
		{
			delete[] data;
		}

		bool alloc( uint32_t inSize )
		{
			data = new T[ inSize ];
			numElements = inSize;
			return true;
		}

		bool free()
		{
			delete[] data;
			numElements = 0;
			return true;
		}

		T& operator[]( uint32_t index )
		{
			ASSERT( index < numElements );
			return data[ index ];
		}

		const T& operator[]( uint32_t index ) const
		{
			ASSERT( index < numElements );
			return data[ index ];
		}

		uint32_t size() const
		{
			return numElements;
		}

	private:
		T* data;
		uint32_t numElements;
	};
}

#endif