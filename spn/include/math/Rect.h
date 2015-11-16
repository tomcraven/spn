#ifndef MATH_RECT_H
#define MATH_RECT_H

#include "core/Assert.h"
#include "component/Position.h"
#include "component/Dimensions.h"

namespace math
{
	template< class T >
	class Rect
	{
	public:
		static Rect createFromPositionAndDimensions( const component::Position& p, const component::Dimensions& d )
		{
			return Rect< float >(
				p.x, p.y,
				static_cast< float >( d.width ), static_cast< float >( d.height ) );
		}

		Rect( const T& _x,
			const T& _y,
			const T& _w,
			const T& _h ) : x( _x ), y( _y ), w( _w ), h( _h )
		{
		}

		void operator=( const Rect< T >& other )
		{
			x = other.x;
			y = other.y;
			w = other.w;
			h = other.h;
		}
		
		void set( const T& _x,
			const T& _y,
			const T& _w,
			const T& _h )
		{
			x = _x;
			y = _y;
			w = _w;
			h = _h;
		}

		bool containsPoint( const T& pointX, const T& pointY )
		{
			return math::intersect::pointRect( 
				pointX, pointY,
				x, y, w, h );
		}

		T x, y, w, h;
	};
}

#endif