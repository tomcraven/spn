#include <gtest/gtest.h>
#include "core/AssetPool.h"

namespace
{
	class AssetPool : public testing::Test
	{
	protected:
		core::AssetPool<uint32_t> assetPool;
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
