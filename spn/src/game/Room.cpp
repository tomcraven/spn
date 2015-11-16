#include "game/Room.h"
#include "core/Algorithm.h"
#include "core/Assert.h"
#include "core/Time.h"
#include "input/Input.h"
#include "tween/TweenFactory.h"
#include "async/Thread.h"

namespace
{
	const float kTimeStepSeconds = 1.0f / 60.0f;
	const uint32_t kTimeStepMilliseconds = uint32_t( kTimeStepSeconds * 1000.0f );
}

namespace game
{
	bool Room::go()
	{
		while ( !shouldExit() )
		{
			VALIDATE( onUpdateStart() );

			VALIDATE( update() );
			VALIDATE( render() );

			VALIDATE( onUpdateEnd( kTimeStepMilliseconds ) );
		}

		return true;
	}

	bool Room::shutdown()
	{
		VALIDATE( tween::TweenFactory::get().removeAllTweens() );
		return true;
	}

	bool Room::render()
	{
		return true;
	}

	bool Room::shouldExit()
	{
		return input::Input::userHasRequestedToExit();
	}

	bool Room::update()
	{
		VALIDATE( input::Input::get().update() );
		VALIDATE( tween::TweenFactory::get().update( getTimeStepSeconds() ) );

		return true;
	}

	bool Room::onUpdateStart()
	{
		VALIDATE( core::Time::getMilliseconds( updateStartMilliseconds ) );
		return true;
	}

	bool Room::onUpdateEnd( uint32_t timeStepMilliseconds )
	{
		uint64_t endMilliseconds;
		VALIDATE( core::Time::getMilliseconds( endMilliseconds ) );
		uint32_t totalUpdateMilliseconds = uint32_t( endMilliseconds - updateStartMilliseconds );
		int32_t remainingUpdateTimeMilliseconds = int32_t( timeStepMilliseconds ) - totalUpdateMilliseconds;
		float yieldTimeMilliseconds = static_cast< float >( core::algorithm::max( 0, remainingUpdateTimeMilliseconds ) );
		async::Thread::sleep( yieldTimeMilliseconds / 1000.0f );

		return true;
	}

	float Room::getTimeStepSeconds()
	{
		return kTimeStepSeconds;
	}
}