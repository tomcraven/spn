#ifndef MATH_INTERSECT_H
#define MATH_INTERSECT_H

#include "core/Types.h"
#include "core/Algorithm.h"

namespace math
{
	namespace intersect
	{
		static bool pointRect( int32_t pointX, int32_t pointY,
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
		
		static bool circleRect( int32_t circleX, int32_t circleY, uint32_t circleRadius,
				int32_t rectX, int32_t rectY, uint32_t rectWidth, uint32_t rectHeight )
		{
			if ( pointRect( circleX, circleY, rectX, rectY, rectWidth, rectHeight ) )
			{
				return true;
			}
			else
			{
				// http://stackoverflow.com/a/1879223/475974
				uint32_t closestX = core::algorithm::clamp(circleX, rectX, rectX + static_cast< int32_t >( rectWidth ) );
				uint32_t closestY = core::algorithm::clamp(circleY, rectY, rectY + static_cast< int32_t >( rectHeight ) );

				// Calculate the distance between the circle's center and this closest point
				uint32_t distanceX = circleX - closestX;
				uint32_t distanceY = circleY - closestY;

				// If the distance is less than the circle's radius, an intersection occurs
				float distanceSquared = static_cast< float >( (distanceX * distanceX) + (distanceY * distanceY) );
				return distanceSquared < (circleRadius * circleRadius);
			}
		}
	};
}

#endif