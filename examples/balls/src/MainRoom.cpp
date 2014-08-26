#include "MainRoom.h"
#include "core/Algorithm.h"
#include "core/Assert.h"
#include "core/Time.h"
#include "draw/Draw.h"

#include "component/Position.h"

#include "Iw2D.h"

namespace
{
	const uint32_t kNumBalls = 100;
}

bool MainRoom::init()
{
	balls = new Ball[kNumBalls];

	for ( uint32_t i = 0; i < kNumBalls; ++i )
	{
		CHECK( balls[i].init() );
	}

	return true;
}

bool MainRoom::shutdown()
{
	delete[] balls;
	return true;
}

bool MainRoom::update()
{
	CHECK( Room::update() );

	for ( uint32_t i = 0; i < kNumBalls; ++i )
	{
		CHECK( balls[i].update( getTimeStepSeconds() ) );
	}

	return true;
}

bool MainRoom::render()
{
	CHECK( draw::Draw::get().clear( 0xFF000000 ) );

	for ( uint32_t i = 0; i < kNumBalls; ++i )
	{
		CHECK( balls[i].render() );
	}

	CHECK( draw::Draw::get().flip() );
	return true;
}