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
	freeBalls = new Ball[kNumBalls];

	for ( uint32_t i = 0; i < kNumBalls; ++i )
	{
		balls.push_back( &freeBalls[i] );

		CHECK( balls[i]->init() );
		balls[i]->setConsumer( this );
	}

	return true;
}

bool MainRoom::shutdown()
{
	delete[] freeBalls;
	return true;
}

bool MainRoom::update()
{
	CHECK( Room::update() );
	
	std::vector< Ball* >::iterator ballIter = balls.begin();
	for ( ; ballIter != balls.end(); ++ballIter )
	{
		CHECK( ( *ballIter )->update( getTimeStepSeconds() ) );
	}

	return true;
}

bool MainRoom::render()
{
	CHECK( draw::Draw::get().clear( 0xFF000000 ) );
	
	std::vector< Ball* >::iterator ballIter = balls.begin();
	for ( ; ballIter != balls.end(); ++ballIter )
	{
		CHECK( ( *ballIter )->render() );
	}

	CHECK( draw::Draw::get().flip() );
	return true;
}

bool MainRoom::onButtonConsumerClick( uint32_t id )
{
	std::vector< Ball* >::iterator ballIter = balls.begin();
	for ( ; ballIter != balls.end(); ++ballIter )
	{
		if ( ( *ballIter )->getId() == id )
		{
			balls.erase( ballIter );
			break;
		}
	}

	return true;
}