#include "core/Assert.h"
#include "component/AngularVelocity.h"
#include "component/Rotation.h"
#include "component/ComponentEntity.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	AngularVelocity::AngularVelocity() : v( 0.0f ), r( 0 )
	{
	}

	AngularVelocity::AngularVelocity( float inV ) : v( inV ), r( 0 )
	{
	}

	bool AngularVelocity::init( ComponentEntity* entity )
	{
		VALIDATE( entity->getComponent< Rotation >( &r ) );
		return true;
	}

	bool AngularVelocity::update( ComponentEntity* entity, float timeStep )
	{
		r->r += v * timeStep;

		return true;
	}

	uint32_t AngularVelocity::getType()
	{
		return typeId;
	}

	void AngularVelocity::set( float value )
	{
		v = value;
	}
	
	void AngularVelocity::set( const AngularVelocity& other )
	{
		v = other.v;
		r = other.r;
	}

} // component