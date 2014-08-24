#include "component/Velocity.h"
#include "component/Position.h"
#include "component/IComponent.h"
#include "component/ComponentEntity.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	bool Velocity::update( ComponentEntity* entity, float timeStep )
	{
		Position* p = entity->getComponent<Position>();

		p->x += x * timeStep;
		p->y += y * timeStep;

		return true;
	}

	uint32_t Velocity::getType()
	{
		return typeId;
	}

	bool Velocity::needsUpdating()
	{
		return true;
	}
} // component