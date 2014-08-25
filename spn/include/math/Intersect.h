#ifndef MATH_INTERSECT_H
#define MATH_INTERSECT_H

#include "core/Types.h"

namespace math
{
	class Intersect
	{
	public:
		static bool pointRect( uint32_t pointX, uint32_t pointY,
			uint32_t rectX, uint32_t rectY, uint32_t rectWidth, uint32_t rectHeight );
	};
}

#endif