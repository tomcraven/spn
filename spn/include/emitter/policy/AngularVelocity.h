#ifndef EMITTER_POLICY_ANGULARVELOCITY_H
#define EMITTER_POLICY_ANGULARVELOCITY_H

#include "component/AngularVelocity.h"
#include "core/Rand.h"

namespace emitter
{
	namespace policy
	{
		class AngularVelocity
		{
		public:
			virtual component::AngularVelocity getAngularVelocity() = 0;
		};

		namespace angularvelocity
		{
			class Random : public AngularVelocity
			{
			public:
				Random( float inMin, float inMax ) : min( inMin ), max( inMax )
				{
				}

			public:
				virtual component::AngularVelocity getAngularVelocity()
				{
					return component::AngularVelocity( core::random::range( min, max ) );
				}

			private:
				float min, max;
			};
		}
	}
}

#endif