#include "emitter/Emitter.h"
#include "core/Assert.h"
#include "emitter/policy/Position.h"
#include "emitter/policy/Velocity.h"
#include "emitter/policy/AngularVelocity.h"
#include "emitter/policy/Emission.h"
#include "emitter/policy/Life.h"
#include "emitter/policy/Scale.h"
#include "emitter/policy/Texture.h"
#include "emitter/policy/Initialise.h"

#include <stdio.h>

Emitter::Emitter() : scalePolicy( 0 ), initialisePolicy( 0 )
{
}

bool Emitter::init( uint32_t numParticles )
{
	VALIDATE( particlePool.init( numParticles ) );
	return true;
}

bool Emitter::shutdown()
{
	core::List< emitter::Particle* >::Iterator particleIter = particles.begin();
	for ( ; particleIter != particles.end() ; )
	{
		particlePool.free( *particleIter );
		particleIter = particles.erase( particleIter );	
	}

	VALIDATE( particlePool.shutdown() );
	return true;
}

void Emitter::setPositionPolicy( emitter::policy::Position* inPositionPolicy )
{
	positionPolicy = inPositionPolicy;
}

void Emitter::setVelocityPolicy( emitter::policy::Velocity* inVelocityPolicy )
{
	velocityPolicy = inVelocityPolicy;
}

void Emitter::setTexturePolicy( emitter::policy::Texture* inTexturePolicy )
{
	texturePolicy = inTexturePolicy;
}

void Emitter::setEmissionPolicy( emitter::policy::Emission* inEmissionPolicy )
{
	emissionPolicy = inEmissionPolicy;
}

void Emitter::setLifePolicy( emitter::policy::Life* inLifePolicy )
{
	lifePolicy = inLifePolicy;
}

void Emitter::setScalePolicy( emitter::policy::Scale* inScalePolicy )
{
	scalePolicy = inScalePolicy;
}

void Emitter::setInitialisePolicy( emitter::policy::Initialise* inInitialisePolicy )
{
	initialisePolicy = inInitialisePolicy;
}

void Emitter::setAngularVelocityPolicy( emitter::policy::AngularVelocity* inAgularVelocityPolicy )
{
	angularVelocityPolicy = inAgularVelocityPolicy;
}

bool Emitter::update( float timeStep )
{
	if ( emissionPolicy->shouldEmit( timeStep ) )
	{
		VALIDATE( emitParticle() );

		while ( emissionPolicy->shouldEmitAgain( timeStep ) )
		{
			VALIDATE( emitParticle() );
		}
	}

	core::List< emitter::Particle* >::Iterator particleIter = particles.begin();
	for ( ; particleIter != particles.end() ; )
	{
		if ( !( *particleIter )->update( timeStep ) )
		{
			particleIter = particles.erase( particleIter );
			particlePool.free( *particleIter );
		}
		else
		{
			++particleIter;
		}
	}

	return true;
}

bool Emitter::render()
{
	core::List< emitter::Particle* >::Iterator particleIter = particles.begin();
	for ( ; particleIter != particles.end() ; ++particleIter )
	{
		VALIDATE( ( *particleIter )->render() );
	}

	return true;
}

bool Emitter::emitParticle()
{
	emitter::Particle* newParticle = particlePool.alloc();
	VALIDATE( newParticle );
	VALIDATE( newParticle->init() );

	VALIDATE( positionPolicy );
	USE_COMPONENT_PTR( newParticle, component::Position, set( positionPolicy->getPosition() ) );

	VALIDATE( texturePolicy );
	USE_COMPONENT_PTR( newParticle, component::Texture, setTexturePath( texturePolicy->getTexturePath() ) );

	VALIDATE( lifePolicy );
	newParticle->setTimeToLive( lifePolicy->getTimeToLive() );

	VALIDATE( velocityPolicy );
	USE_COMPONENT_PTR( newParticle, component::Velocity, set( velocityPolicy->getVelocity() ) );

	VALIDATE( angularVelocityPolicy )
	USE_COMPONENT_PTR( newParticle, component::AngularVelocity, set( angularVelocityPolicy->getAngularVelocity() ) );

	if ( scalePolicy )
	{
		USE_COMPONENT_PTR( newParticle, component::Scale, set( scalePolicy->getScale() ) );
	}

	if ( initialisePolicy )
	{
		VALIDATE( initialisePolicy->initParticle( newParticle ) );
	}
	
	VALIDATE( newParticle->init() );
	particles.push_back( newParticle );

	return true;
}