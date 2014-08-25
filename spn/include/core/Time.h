#ifndef CORE_TIME_H
#define CORE_TIME_H

#include "core/Types.h"

namespace core
{
	class Time
	{
	public:
		static bool getMilliseconds( uint64_t &outMilliseconds );
		static bool getSeconds( float &outSeconds );
	};
}

#endif