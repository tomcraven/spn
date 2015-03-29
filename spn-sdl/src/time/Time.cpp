#include "core/Time.h"
#include "core/Assert.h"

namespace core
{
	bool Time::getMilliseconds( uint64_t &outMilliseconds )
	{
		outMilliseconds = 0;
		return true;
	}

	bool Time::getSeconds( float &outSeconds )
	{
		outSeconds = 0;
		return true;
	}
}