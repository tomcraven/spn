#ifndef EMITTER_POLICY_INITIALISE_H
#define EMITTER_POLICY_INITIALISE_H

#include "core/Rand.h"

namespace emitter
{
	class Particle;

	namespace policy
	{
		class Initialise
		{
		public:
			virtual bool initParticle( emitter::Particle* p ) = 0;
		};
	}
}

#endif