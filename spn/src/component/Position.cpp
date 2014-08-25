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