#include "emitter/Particle.h"
#include "core/Assert.h"
#include "draw/ScopedColour.h"

#include <stdio.h>

namespace emitter
{
	Particle::Particle() : c( 0xFF, 255, 145, 0 )
	{
		attach( &p );
		attach( &v );
		attach( &rot );
		attach( &t );
		attach( &r );
		attach( &s );
		attach( &av );
		attach( &c );
		attach( &d );
	}

	bool Particle::render()
	{
		draw::ScopedColour scopedColour( c.serialise() );

		VALIDATE( r.render( p, rot, s ) );
		return true;
	}

	bool Particle::update( float timeStep )
	{
		VALIDATE( component::ComponentEntity::update( timeStep ) );

		timeUntilDeath -= timeStep;
		return timeUntilDeath > 0.0f;
	}

	void Particle::setTimeToLive( float inTimeToLive )
	{
		timeUntilDeath = inTimeToLive;
		totalLife = inTimeToLive;
	}

	float Particle::getAge()
	{
		return timeUntilDeath / totalLife;
	}

	float Particle::getTimeToLive()
	{
		return totalLife;
	}
}