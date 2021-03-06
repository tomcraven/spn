#ifndef GAME_TRANSITION_FADEOUT_H
#define GAME_TRANSITION_FADEOUT_H

#include "game/transition/ITransition.h"

namespace game
{
	namespace transition
	{
		class FadeOut : public ITransition
		{
		public:
			explicit FadeOut( uint32_t colour, float timeoutSeconds );
			
			bool startIn( float seconds );

		public: // ITransition
			bool render();
			bool update( float timeStepSeconds );
			bool start();

		private:
			bool updateTransition( float timeStepSeconds );
			bool updateDelay( float timeStepSeconds );
			bool updateNull( float timeStepSeconds );

			uint32_t colour;
			uint32_t fadeOutAlpha;
			float timeoutSeconds;
			float delaySeconds;
		
			bool ( FadeOut::*updateFunction )( float timeStepSeconds );
		};
	}
}

#endif