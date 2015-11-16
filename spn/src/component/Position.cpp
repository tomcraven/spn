#include "component/Position.h"
#include "core/Algorithm.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	Position::Position() : x( 0.0f ), y( 0.0f )
	{
	}
	
	Position::Position( float inX, float inY ) : x( inX ), y( inY )
	{
	}
	
	Position::Position( int32_t inX, int32_t inY ) : 
		x( static_cast< float >( inX ) ), y( static_cast< float >( inY ) )
	{
	}

	Position::Position( uint32_t inX, uint32_t inY ) : 
		x( static_cast< float >( inX ) ), y( static_cast< float >( inY ) )
	{
	}

	void Position::set( float inX, float inY )
	{
		x = inX;
		y = inY;
	}

	void Position::set( const Position& other )
	{
		x = other.x;
		y = other.y;
	}

	float Position::squaredDistanceTo( const Position& other ) const
	{
		float xDiff = x - other.x;
		float yDiff = y - other.y;
		return ( xDiff * xDiff ) + ( yDiff * yDiff );
	}

	bool Position::operator==( const Position& other )
	{
		return core::algorithm::floatEquals( x, other.x ) &&
			core::algorithm::floatEquals( y, other.y );
	}

	uint32_t Position::getType()
	{
		return typeId;
	}
} // component