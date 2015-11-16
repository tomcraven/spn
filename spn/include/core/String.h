#ifndef CORE_STRING_H
#define CORE_STRING_H

#include "core/Types.h"

namespace core
{
	class String
	{
	public:
		String();
		String( const char* str );
		~String();
		bool reserve( uint32_t size );

		void operator=( const char* str );
		void operator+=( const char* str );


		const char* c_str();
		char* str();

		uint32_t size();

	private:
		char* data;
		uint32_t dataSize;
	};
}

#endif