#ifndef EMITTER_POLICY_LIFE_H
#define EMITTER_POLICY_LIFE_H

#include "core/Rand.h"

namespace emitter
{
	namespace policy
	{
		class Life
		{
		public:
			virtual float getTimeToLive() = 0;
		};

		namespace life
		{
			class Static : public Life
			{
			public:
				Static( float inTimeToLive ) : timeToLive( inTimeToLive )
				{
				}

			public:
				virtual float getTimeToLive()
				{
					return timeToLive;
				}

			private:
				float timeToLive;
			};
		
			class Random : public Life
			{
			public:
				Random( float inTimeToLiveLow, float inTimeToLiveHigh ) : 
					timeToLiveLow( inTimeToLiveLow ), timeToLiveHigh( inTimeToLiveHigh )
				{
				}

			public:
				virtual float getTimeToLive()
				{
					return core::random::range( timeToLiveLow, timeToLiveHigh );
				}

			private:
				float timeToLiveLow, timeToLiveHigh;
			};
		}
	}
}

#endif