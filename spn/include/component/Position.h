#ifndef COMPONENT_POSITION_H
#define COMPONENT_POSITION_H

#include "component/IComponent.h"

namespace component
{
	class Position : public IComponent
	{
	public:
		Position();
		Position( float x, float y );
		Position( int32_t x, int32_t y );
		Position( uint32_t x, uint32_t y );
		
		template< class T >
		void set( const T& inX, const T& inY )
		{
			x = static_cast< float >( inX );
			y = static_cast< float >( inY );
		}

		void set( float x, float y );
		void set( const Position& other );

		float squaredDistanceTo( const Position& other ) const;

		bool operator==( const Position& other );

		float x, y;

	public: // Component
		virtual uint32_t getType();
	};
}

#endif