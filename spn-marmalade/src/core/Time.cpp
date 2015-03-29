#include "core/Time.h"
#include "core/Assert.h"

#include "s3e.h"

namespace core
{
	bool Time::getMilliseconds( uint64_t &outMilliseconds )
	{
		outMilliseconds = s3eTimerGetMs( );
		return s3eTimerGetError( ) == S3E_TIMER_ERR_NONE;
	}

	bool Time::getSeconds( float &outSeconds )
	{
		uint64_t milliseconds;
		VALIDATE( Time::getMilliseconds( milliseconds ) );
		outSeconds = float( milliseconds ) / 1000.0f;
		return true;
	}
}