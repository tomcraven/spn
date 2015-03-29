#ifndef EMITTER_H
#define EMITTER_H

#include "component/Velocity.h"
#include "component/Position.h"
#include "component/Dimensions.h"
#include "emitter/Particle.h"
#include "core/List.h"
#include "core/AssetPool.h"
#include "core/Rand.h"
#include "math/Math.h"

namespace emitter
{
	namespace policy
	{
		class Position;
		class Velocity;
		class AngularVelocity;
		class Emission;
		class Life;
		class Scale;
		class Texture;
		class Initialise;
	}
}

class Emitter
{
public:
	Emitter();

	bool init( uint32_t numParticles );
	bool shutdown();

	void setPositionPolicy( emitter::policy::Position* positionPolicy );
	void setVelocityPolicy( emitter::policy::Velocity* velocityPolicy );
	void setTexturePolicy( emitter::policy::Texture* texturePolicy );
	void setEmissionPolicy( emitter::policy::Emission* emissionPolicy );
	void setLifePolicy( emitter::policy::Life* lifePolicy );
	void setScalePolicy( emitter::policy::Scale* scalePolicy );
	void setInitialisePolicy( emitter::policy::Initialise* initialisePolicy );
	void setAngularVelocityPolicy( emitter::policy::AngularVelocity* angularVelocityPolicy );

	bool update( float timeStep );
	bool render();

private:
	bool emitParticle();

	emitter::policy::Position* positionPolicy;
	emitter::policy::Velocity* velocityPolicy;
	emitter::policy::Texture* texturePolicy;
	emitter::policy::Emission* emissionPolicy;
	emitter::policy::Life* lifePolicy;
	emitter::policy::Scale* scalePolicy;
	emitter::policy::Initialise* initialisePolicy;
	emitter::policy::AngularVelocity* angularVelocityPolicy;

private:
	core::AssetPool< emitter::Particle > particlePool;
	core::List< emitter::Particle* > particles;
};

#endif