#ifndef CORE_RAND_H
#define CORE_RAND_H

#include <stdlib.h>

namespace core
{
	namespace random
	{
		static float __rand()
		{
			return ( ::rand() % 1000 ) / 1000.0f;
		}

		static float range( float low, float high )
		{
			return low + ( __rand() * ( high - low ) );
		}

		static float range( float high )
		{
			return __rand() * high;
		}

		static bool boolean()
		{
			return __rand() > 0.5f;
		}
	}
}

#endif