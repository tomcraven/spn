#include "core/Assert.h"
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
	bool Velocity::init( ComponentEntity* entity )
	{
		CHECK( entity->getComponent< Position >( &p ) );
		return true;
	}

	bool Velocity::update( ComponentEntity* entity, float timeStep )
	{
		p->x += x * timeStep;
		p->y += y * timeStep;

		return true;
	}

	uint32_t Velocity::getType()
	{
		return typeId;
	}
} // component