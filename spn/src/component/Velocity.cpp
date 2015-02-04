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
	Velocity::Velocity() : x( 0.0f ), y( 0.0f ), p( 0 )
	{
	}

	Velocity::Velocity( float inX, float inY ) : x( inX ), y( inY ), p( 0 )
	{
	}

	bool Velocity::init( ComponentEntity* entity )
	{
		VALIDATE( entity->getComponent< Position >( &p ) );
		return true;
	}

	bool Velocity::update( ComponentEntity* entity, float timeStep )
	{
		p->x += x * timeStep;
		p->y += y * timeStep;

		return true;
	}

	void Velocity::set( float inX, float inY )
	{
		x = inX;
		y = inY;
	}

	void Velocity::set( const Velocity& other )
	{
		x = other.x;
		y = other.y;
	}

	uint32_t Velocity::getType()
	{
		return typeId;
	}
} // component