#include "core/Assert.h"
#include "component/Velocity.h"
#include "component/Position.h"
#include "component/Speed.h"
#include "component/IComponent.h"
#include "component/ComponentEntity.h"
#include "math/Math.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();

	component::Speed defaultSpeed( 1.0f );
}

namespace component
{
	Velocity::Velocity() : x( 0.0f ), y( 0.0f ), p( 0 )
	{
	}

	Velocity::Velocity( float inX, float inY ) : x( inX ), y( inY ), p( 0 )
	{
	}

	bool Velocity::initComponent( ComponentEntity* entity )
	{
		VALIDATE( entity->getComponent< Position >( &p ) );

		// Entity may not have a speed component
		if ( !entity->getComponent< Speed >( &s ) )
		{
			s = &defaultSpeed;
		}

		return true;
	}

	bool Velocity::update( ComponentEntity* entity, float timeStep )
	{
		p->x += x * timeStep * s->s;
		p->y += y * timeStep * s->s;

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

	void Velocity::unit()
	{
		float length = sqrtf( ( x * x ) + ( y * y ) );
		x /= length;
		y /= length;
	}

	void Velocity::multiply( float val )
	{
		x *= val;
		y *= val;
	}

	uint32_t Velocity::getType()
	{
		return typeId;
	}
} // component