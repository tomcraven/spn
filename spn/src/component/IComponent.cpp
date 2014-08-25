#include "component/IComponent.h"

namespace
{
	uint32_t componentId = 0;
}

namespace component
{
	uint32_t IComponent::generateTypeId()
	{
		return componentId++;
	}
}