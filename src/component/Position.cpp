#include "component/Position.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	uint32_t Position::getType()
	{
		return typeId;
	}

	bool Position::needsUpdating()
	{
		return false;
	}
} // component