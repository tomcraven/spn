#include "component/Scale.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	Scale::Scale( float inScale ) : scale( inScale )
	{
	}
	
	void Scale::set( float inScale )
	{
		scale = inScale;
	}

	uint32_t Scale::getType()
	{
		return typeId;
	}
} // component