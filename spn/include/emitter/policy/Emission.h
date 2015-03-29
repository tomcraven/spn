#ifndef EMITTER_POLICY_EMISSION_H
#define EMITTER_POLICY_EMISSION_H

namespace emitter
{
	namespace policy
	{
		class Emission
		{
		public:
			virtual bool shouldEmit( float timeStep ) = 0;
			virtual bool shouldEmitAgain( float timeStep ) = 0;
		};

		namespace emission
		{
			class Timed : public Emission
			{
			public:
				Timed( float inTime ) : timeUntilEmit( inTime ), time( inTime )
				{
				}

			public:
				virtual bool shouldEmit( float timeStep )
				{
					timeUntilEmit -= timeStep;
					if ( timeUntilEmit <= 0.0f )
					{
						timeUntilEmit += time;
						return true;
					}

					return false;
				}

				virtual bool shouldEmitAgain( float timeStep )
				{
					if ( timeUntilEmit <= 0.0f )
					{
						timeUntilEmit += time;
						return true;
					}

					return false;
				}

			private:
				float timeUntilEmit;
				float time;
			};
		}
	}
}

#endif