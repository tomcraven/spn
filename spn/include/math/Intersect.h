#ifndef MATH_INTERSECT_H
#define MATH_INTERSECT_H

#include "core/Types.h"
#include "core/Algorithm.h"

namespace math
{
	namespace intersect
	{
		static bool pointRect( float pointX, float pointY,
			float rectX, float rectY, float rectWidth, float rectHeight )
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
		
		static bool circleRect( float circleX, float circleY, float circleRadius,
				float rectX, float rectY, float rectWidth, float rectHeight )
		{
			if ( pointRect( circleX, circleY, rectX, rectY, rectWidth, rectHeight ) )
			{
				return true;
			}
			else
			{
				// http://stackoverflow.com/a/1879223/475974
				float closestX = core::algorithm::clamp(circleX, rectX, rectX + rectWidth );
				float closestY = core::algorithm::clamp(circleY, rectY, rectY + rectHeight );

				// Calculate the distance between the circle's center and this closest point
				float distanceX = circleX - closestX;
				float distanceY = circleY - closestY;

				// If the distance is less than the circle's radius, an intersection occurs
				float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
				return distanceSquared < (circleRadius * circleRadius);
			}
		}
	};
}

#endif