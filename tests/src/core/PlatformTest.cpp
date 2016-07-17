#include <gtest/gtest.h>
#include "core/Platform.h"

TEST( Platform, SPRINT_basic )
{
		const uint32_t bufferSize = 8;
		char buffer[bufferSize];
		SPRINTF( buffer, bufferSize, "hello" );
		ASSERT_STREQ( "hello", buffer );
}

TEST( Platform, SPRINTF_interpolate )
{
		const uint32_t bufferSize = 8;
		char buffer[bufferSize];
		SPRINTF( buffer, bufferSize, "%i", 123 );
		ASSERT_STREQ( "123", buffer );
}
