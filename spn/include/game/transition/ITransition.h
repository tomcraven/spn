#ifndef GAME_TRANSITION_H
#define GAME_TRANSITION_H

#include "core/Types.h"

namespace game
{
	namespace transition
	{
		class ITransition
		{
		public:
			class IConsumer
			{
			public:
				virtual bool onTransitionComplete( uint32_t transitionId ) = 0;
			};

			ITransition();
			virtual ~ITransition();
			virtual bool render() = 0;
			virtual bool update( float timeStepSeconds ) = 0;
			virtual bool start() = 0;

			virtual bool setConsumer( IConsumer* consumer );

		protected:
			IConsumer* consumer;
			uint32_t id;
		};
	}
}

#endif