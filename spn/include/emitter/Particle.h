#ifndef EMITTER_PARTICLE_H
#define EMITTER_PARTICLE_H

#include "component/ComponentEntity.h"
#include "component/Position.h"
#include "component/Velocity.h"
#include "component/Rotation.h"
#include "component/Texture.h"
#include "component/RenderTextureCentre.h"
#include "component/Scale.h"
#include "component/AngularVelocity.h"
#include "component/Colour.h"
#include "component/Dimensions.h"

namespace emitter
{
	class Particle : public component::ComponentEntity
	{
	public:
		Particle();
		void setTimeToLive( float timeToLive );
		float getAge();
		float getTimeToLive();

	public: // component::ComponentEntity
		virtual bool render();
		virtual bool update( float timeStep );

	private:
		component::Position p;
		component::Velocity v;
		component::Rotation rot;
		component::Texture t;
		component::RenderTextureCentre r;
		component::Scale s;
		component::AngularVelocity av;
		component::Colour c;
		component::Dimensions d;

		float timeUntilDeath;
		float totalLife;
	};
}

#endif