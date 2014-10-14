#include "game/Room.h"
#include "core/Algorithm.h"
#include "core/Assert.h"
#include "core/Time.h"
#include "input/Input.h"

// Todo - can we remove this include?
#include "s3e.h"

namespace
{
	const float kTimeStepSeconds = 1.0f / 30.0f;
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
		CHECK_S3E_RESULT( s3eKeyboardUpdate() );
		CHECK_S3E_RESULT( s3ePointerUpdate() );

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
		int32_t remainingUpdateTimeMilliseconds = timeStepMilliseconds - totalUpdateMilliseconds;
		uint32_t yieldTimeMilliseconds = core::algorithm::max( 0, remainingUpdateTimeMilliseconds );
        s3eDeviceYield( yieldTimeMilliseconds );

		return true;
	}

	float Room::getTimeStepSeconds()
	{
		return kTimeStepSeconds;
	}
}