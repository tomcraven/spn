#include <gtest/gtest.h>
#include "core/Algorithm.h"
#include "core/Types.h"

using namespace core::algorithm;

TEST( Algorithm, max )
{
	ASSERT_EQ( 2, max( 1, 2 ) );
	ASSERT_FLOAT_EQ( 1.1f, max(1.1f, 0.5f ) );
}

TEST( Algorithm, min )
{
	ASSERT_EQ( 10, min( 10, 100 ) );
	ASSERT_FLOAT_EQ( 123.0f, min( 123.0f, 654.123f ) );
}

TEST( Algorithm, clamp )
{
	ASSERT_EQ( 1, clamp( 123, 0, 1 ) );
	ASSERT_FLOAT_EQ( 123.321f, clamp( 123.321f, 123.321f, 1234.0f ) );
	ASSERT_EQ( 5, clamp( 5, 0, 10 ) );
}

TEST( Algorithm, abs )
{
	ASSERT_EQ( 1, abs( -1 ) );
	ASSERT_EQ( 1, abs( 1 ) );
	ASSERT_FLOAT_EQ( 10.0f, abs( -10.0f ) );
}

TEST( Algorithm, floatEquals )
{
	ASSERT_TRUE( floatEquals( 1.0f, 1.0f ) );
	ASSERT_TRUE( floatEquals( 1.1f, 1.0f, 0.11f ) );

	ASSERT_FALSE( floatEquals( 1.1f, 1.0f ) );
	ASSERT_FALSE( floatEquals( 1.1f, 1.0f, 0.09f ) );
}

TEST( Algorithm, swapUint32 )
{
	uint32_t a = 0u;
	uint32_t b = 10u;
	swap( a, b );

	ASSERT_EQ( 10u, a );
	ASSERT_EQ( 0u, b );
}

TEST( Algorithm, swapFloat )
{
	float a = 1.1f;
	float b = 42.0f;
	swap( a, b );

	ASSERT_FLOAT_EQ( 42.0f, a );
	ASSERT_FLOAT_EQ( 1.1f, b );
}
