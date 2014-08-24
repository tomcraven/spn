#include "math/Intersect.h"

namespace math
{
	bool Intersect::pointRect( uint32_t pointX, uint32_t pointY,
			uint32_t rectX, uint32_t rectY, uint32_t rectWidth, uint32_t rectHeight )
	{
		if ( pointX > ( rectX + rectWidth ) ||
			 pointX < rectX ||
			 pointY > ( rectY + rectHeight ) ||
			 pointY < rectY )
		{
			return false;
		}
		return true;
	}
}