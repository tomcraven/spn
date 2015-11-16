#include "component/InteractBase.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	bool InteractBase::go()
	{
		return false;
	}

	uint32_t InteractBase::getType()
	{
		return typeId;
	}
}