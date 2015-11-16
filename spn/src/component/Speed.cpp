#include "component/Speed.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	Speed::Speed() : s( 1.0f )
	{
	}

	Speed::Speed( float inS ) : s( inS )
	{
	}

	void Speed::set( float val )
	{
		s = val;
	}

	uint32_t Speed::getType()
	{
		return typeId;
	}
} // component