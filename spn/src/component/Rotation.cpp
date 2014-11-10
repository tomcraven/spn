#include "component/Rotation.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	Rotation::Rotation() : r( 0.0f )
	{
	}

	void Rotation::set( float inR )
	{
		r = inR;
	}

	uint32_t Rotation::getType()
	{
		return typeId;
	}
} // component