#include "core/String.h"
#include "core/Assert.h"

#include <string.h>
#include <malloc.h>

namespace core
{
	String::String() : data( 0 ), dataSize( 0 )
	{
	}

	String::String( const char* str ) : String()
	{
		this->operator=( str );
	}

	String::~String()
	{
		if ( data )
		{
			free( data );
		}
	}

	bool String::reserve( uint32_t size )
	{
		///@todo what do we want to do if size <= dataSize ?

		data = reinterpret_cast< char* >( realloc( data, size ) );
		VALIDATE( data );
		dataSize = size;

		if ( size > 0 )
		{
			data[ 0 ] = '\0';
		}

		return true;
	}

	void String::operator=( const char* str )
	{
		if ( str == 0 )
		{
			return;
		}

		uint32_t strLen = strlen( str ) + 1; // + 1 for null terminator
		if ( strLen > dataSize )
		{
			reserve( strLen );
		}

		memcpy( data, str, strLen - 1 );
		data[ strLen - 1 ] = 0;
	}

	void String::operator+=( const char* str )
	{
		uint32_t strLen = strlen( str );
		uint32_t newSize = dataSize + strLen;
		char* newBuffer = reinterpret_cast< char* >( malloc( newSize ) );

		if ( data )
		{
			memcpy( newBuffer, data, dataSize + 1 );
			free( data );
		}

		memcpy( newBuffer + dataSize - 1, str, strLen + 1 );
		dataSize = newSize;
		data = newBuffer;
	}

	const char* String::c_str()
	{
		return str();
	}

	char* String::str()
	{
		return data;
	}

	uint32_t String::size()
	{
		return dataSize;
	}
}