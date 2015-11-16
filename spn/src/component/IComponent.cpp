#include "component/IComponent.h"

namespace component
{
	uint32_t IComponent::generateTypeId()
	{
		static uint32_t componentId = 0;
		return componentId++;
	}
}