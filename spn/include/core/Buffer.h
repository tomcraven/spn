#ifndef CORE_BUFFER_H
#define CORE_BUFFER_H

#include "core/Types.h"

namespace core
{
	template< class T >
	class Buffer
	{
	public:
		Buffer() : data( 0 )
		{
		}

		~Buffer()
		{
			if ( data )
			{
				free( data );
			}
		}

		bool alloc( uint32_t size )
		{
			VALIDATE( !data );
			
			if ( size == 0 )
			{
				return true;
			}

			data = new T[ size ];
			VALIDATE( data );

			return true;
		}

		bool free()
		{
			delete data;
			data = 0;
		}

	private:
		T* data;
	};
}

#endif