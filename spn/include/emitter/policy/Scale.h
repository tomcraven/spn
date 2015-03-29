#ifndef EMITTER_POLICY_SCALE_H
#define EMITTER_POLICY_SCALE_H

#include "core/Rand.h"

namespace emitter
{
	namespace policy
	{
		class Scale
		{
		public:
			virtual float getScale() = 0;
		};

		namespace scale
		{
			class Random : public Scale
			{
			public:
				Random( float inMin, float inMax ) : min( inMin ), max( inMax )
				{
				}

			public:
				virtual float getScale()
				{
					return core::random::range( min, max );
				}

			private:
				float min, max;
			};
		
			class Random2 : public Scale
			{
			public:
				Random2( float inMin1, float inMax1,
						 float inMin2, float inMax2 ) : min1( inMin1 ), max1( inMax1 ),
														min2( inMin2 ), max2( inMax2 )
				{
				}

			public:
				virtual float getScale()
				{
					if ( core::random::boolean() )
					{
						return core::random::range( min1, max1 );
					}
					else
					{
						return core::random::range( min2, max2 );
					}
				}

			private:
				float min1, max1;
				float min2, max2;
			};
		}
	}
}

#endif