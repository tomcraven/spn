#ifndef GAME_TRANSITION_FADEIN_H
#define GAME_TRANSITION_FADEIN_H

#include "game/transition/ITransition.h"

namespace game
{
	namespace transition
	{
		class FadeIn : public ITransition
		{
		public:
			explicit FadeIn( uint32_t colour, float timeoutSeconds );

		public: // ITransition
			bool render();
			bool update( float timeStepSeconds );
			bool start();

		private:
			bool updateTransition( float timeStepSeconds );
			bool updateNull( float timeStepSeconds );

			uint32_t colour;
			uint32_t fadeInAlpha;
			float timeoutSeconds;
		
			bool ( FadeIn::*updateFunction )( float timeStepSeconds );
		};
	}
}

#endif