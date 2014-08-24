#include "game/IRoom.h"
#include "core/Algorithm.h"
#include "core/Assert.h"
#include "core/Time.h"

#include "s3e.h"

namespace game
{
	bool IRoom::update()
	{
		CHECK_S3E_RESULT( s3eKeyboardUpdate() );
		CHECK_S3E_RESULT( s3ePointerUpdate() );

		return true;
	}

	void IRoom::onUpdateStart()
	{
		core::Time::getMilliseconds( updateStartMilliseconds );
	}

	void IRoom::onUpdateEnd( uint32_t timeStepMilliseconds )
	{
		uint64_t endMilliseconds;
		core::Time::getMilliseconds( endMilliseconds );
		uint32_t totalUpdateMilliseconds = uint32_t( endMilliseconds - updateStartMilliseconds );
		int32_t remainingUpdateTimeMilliseconds = timeStepMilliseconds - totalUpdateMilliseconds;
		uint32_t yieldTimeMilliseconds = core::Algorithm::max( 0, remainingUpdateTimeMilliseconds );

        s3eDeviceYield( yieldTimeMilliseconds );
	}
}