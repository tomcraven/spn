#include <gtest/gtest.h>
#include "core/AssetPool.h"

namespace
{
	struct TestType
	{
		uint32_t data;
	};

	class AssetPool : public testing::Test
	{
	protected:
		core::AssetPool<TestType> assetPool;
	};
}

TEST_F( AssetPool, ShouldConstruct )
{
	// tested as part of fixture setup
}

TEST_F( AssetPool, ShouldInit )
{
	ASSERT_TRUE( assetPool.init( 10 ) );
}

TEST_F( AssetPool, ShouldShutdown )
{
	ASSERT_TRUE( assetPool.shutdown() );
}

TEST_F( AssetPool, ShouldFailAllocBeforeInit )
{
	ASSERT_EQ( reinterpret_cast< TestType* >( 0u ), assetPool.alloc() );
}

TEST_F( AssetPool, ShouldAlloc )
{
	ASSERT_TRUE( assetPool.init( 1 ) );
	TestType* t = assetPool.alloc();
	ASSERT_NE( reinterpret_cast< TestType* >( 0 ), t );
}

TEST_F( AssetPool, ShouldFailToAllocWhenExhausted )
{
	const uint32_t size = 10;
	ASSERT_TRUE( assetPool.init( size ));
	for ( uint32_t i = 0; i < size; ++i )
	{
		assetPool.alloc();
	}
	ASSERT_EQ( reinterpret_cast< TestType* >( 0u ), assetPool.alloc() );
}

TEST_F( AssetPool, ShouldAllocAfterFreeWhenExhausted )
{
	ASSERT_TRUE( assetPool.init( 1 ));
	TestType* t = assetPool.alloc();
	ASSERT_NE( reinterpret_cast< TestType* >( 0 ), t );
	ASSERT_EQ( reinterpret_cast< TestType* >( 0 ), assetPool.alloc() );
	ASSERT_TRUE( assetPool.free(t) );
	ASSERT_NE( reinterpret_cast< TestType* >( 0 ), assetPool.alloc() );
}

TEST_F( AssetPool, ShouldFailFreeIfAssetIsInvalid )
{
	TestType t;
	ASSERT_FALSE( assetPool.free( &t ) );
}

TEST_F( AssetPool, ShouldGetNumFreeAssets )
{
	ASSERT_EQ( 0u, assetPool.getNumFreeAssets() );

	const uint32_t size = 10;
	ASSERT_TRUE( assetPool.init( size ) );
	
	const uint32_t numAllocs = 3;
	for ( uint32_t i = 0; i < numAllocs; ++i )
	{
		ASSERT_NE( reinterpret_cast< TestType* >( 0 ), assetPool.alloc() );
	}

	ASSERT_EQ( size - numAllocs, assetPool.getNumFreeAssets() );
}