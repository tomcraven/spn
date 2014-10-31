#ifndef MATH_INTERSECT_H
#define MATH_INTERSECT_H

#include "core/Types.h"

namespace math
{
	class Intersect
	{
	public:
		static bool pointRect( int32_t pointX, int32_t pointY,
			int32_t rectX, int32_t rectY, uint32_t rectWidth, uint32_t rectHeight );
	};
}

#endif