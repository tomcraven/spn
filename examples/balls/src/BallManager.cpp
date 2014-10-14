#include "BallManager.h"
#include "MainRoom.h"
#include "core/Assert.h"
#include <stdio.h>

BallManager::BallManager( MainRoom* inMainRoom ) : 
	clickedBallCount( 0 ),
	mainRoom( inMainRoom )
{
}

bool BallManager::init( uint32_t numBalls )
{
	freeBalls = new Ball[ numBalls ];
	for ( uint32_t i = 0; i < numBalls; ++i )
	{
		balls.push_back( &freeBalls[i] );

		VALIDATE( balls[i]->init() );
		balls[i]->setConsumer( this );
	}

	ballToErase = balls.end();

	VALIDATE( updateClickedBallCountBuffer() );

	return true;
}

bool BallManager::shutdown()
{
	BallContainer::iterator ballIter = balls.begin();
	for ( ; ballIter != balls.end(); ++ballIter )
	{
		VALIDATE( ( *ballIter )->shutdown() );
	}
	balls.clear();
	delete[] freeBalls;

	return true;
}

bool BallManager::update( float timeStepSeconds )
{
	BallContainer::iterator ballIter = balls.begin();
	for ( ; ballIter != balls.end(); ++ballIter )
	{
		VALIDATE( ( *ballIter )->update( timeStepSeconds ) );
	}

	if ( ballToErase != balls.end() )
	{
		VALIDATE( ( *ballToErase )->shutdown() );
		balls.erase( ballToErase );
		ballToErase = balls.end();
		
		if ( balls.size() == 0 )
		{
			mainRoom->onEndOfGame();
		}
	}

	return true;
}

bool BallManager::render()
{
	BallContainer::iterator ballIter = balls.begin();
	for ( ; ballIter != balls.end(); ++ballIter )
	{
		VALIDATE( ( *ballIter )->render() );
	}

	return true;
}

const char* BallManager::getNumClickedBallsString()
{
	return clickedBallCountBuffer;
}

bool BallManager::onButtonConsumerClick( uint32_t id )
{
	BallContainer::iterator ballIter = balls.begin();
	for ( ; ballIter != balls.end(); ++ballIter )
	{
		if ( ( *ballIter )->getId() == id )
		{
			ballToErase = ballIter;
			++clickedBallCount;
			VALIDATE( updateClickedBallCountBuffer() );
			break;
		}
	}

	return true;
}

bool BallManager::updateClickedBallCountBuffer()
{
	// todo - check the return code of this
	snprintf( clickedBallCountBuffer, kClickedBallCountBufferSize, "%u\0", clickedBallCount );
	return true;
}