#include "game/Room.h"
#include "core/Algorithm.h"
#include "core/Assert.h"
#include "core/Time.h"

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
			onUpdateStart();

			CHECK( update() );
			CHECK( render() );

			onUpdateEnd( kTimeStepMilliseconds );
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
		return s3eDeviceCheckQuitRequest();
	}

	bool Room::update()
	{
		CHECK_S3E_RESULT( s3eKeyboardUpdate() );
		CHECK_S3E_RESULT( s3ePointerUpdate() );

		return true;
	}

	void Room::onUpdateStart()
	{
		core::Time::getMilliseconds( updateStartMilliseconds );
	}

	void Room::onUpdateEnd( uint32_t timeStepMilliseconds )
	{
		uint64_t endMilliseconds;
		core::Time::getMilliseconds( endMilliseconds );
		uint32_t totalUpdateMilliseconds = uint32_t( endMilliseconds - updateStartMilliseconds );
		int32_t remainingUpdateTimeMilliseconds = timeStepMilliseconds - totalUpdateMilliseconds;
		uint32_t yieldTimeMilliseconds = core::Algorithm::max( 0, remainingUpdateTimeMilliseconds );

        s3eDeviceYield( yieldTimeMilliseconds );
	}

	float Room::getTimeStepSeconds()
	{
		return kTimeStepSeconds;
	}
}