#include "math/Intersect.h"

namespace math
{
	bool Intersect::pointRect( int32_t pointX, int32_t pointY,
			int32_t rectX, int32_t rectY, uint32_t rectWidth, uint32_t rectHeight )
	{
		if ( pointX > ( rectX + static_cast< int32_t >( rectWidth ) ) ||
			 pointX < rectX ||
			 pointY > ( rectY + static_cast< int32_t >( rectHeight ) ) ||
			 pointY < rectY )
		{
			return false;
		}
		return true;
	}
}