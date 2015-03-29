#ifndef EMITTER_POLICY_VELOCITY_H
#define EMITTER_POLICY_VELOCITY_H

#include "component/Velocity.h"

namespace emitter
{
	namespace policy
	{
		class Velocity
		{
		public:
			virtual component::Velocity getVelocity() = 0;
		};

		namespace velocity
		{
			class Static : public Velocity
			{
			public:
				Static( float inX, float inY ) : x( inX ), y( inY )
				{
				}

			public:
				virtual component::Velocity getVelocity()
				{
					return component::Velocity( x, y );
				}

			private:
				float x, y;
			};

			class Circular : public Velocity
			{
			public:
				Circular( float inMinAngle, float inMaxAngle, float inMinRadius, float inMaxRadius ) :
					minAngle( inMinAngle ), maxAngle( inMaxAngle ), 
					minRadius( inMinRadius ), maxRadius( inMaxRadius )
				{
				}

			public:
				virtual component::Velocity getVelocity()
				{
					float randomPosition = core::random::range( minAngle, maxAngle );
					float randomRadius = core::random::range( minRadius, maxRadius );
					float xVelocity = randomRadius * static_cast< float >( cos( randomPosition ) );
					float yVelocity = randomRadius * static_cast< float >( sin( randomPosition ) );

					return component::Velocity( xVelocity, yVelocity );
				}

			private:
				float minAngle, maxAngle;
				float minRadius, maxRadius;
			};
		}
	}
}

#endif