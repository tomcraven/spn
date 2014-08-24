#include "component/Dimensions.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	uint32_t Dimensions::getType()
	{
		return typeId;
	}

	bool Dimensions::needsUpdating()
	{
		return false;
	}
}