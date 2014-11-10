#include "component/Position.h"

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

	void Position::set( float inX, float inY )
	{
		x = inX;
		y = inY;
	}

	uint32_t Position::getType()
	{
		return typeId;
	}
} // component