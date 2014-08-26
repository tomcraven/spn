#ifndef GAME_IROOM_H
#define GAME_IROOM_H

#include "core/Types.h"

namespace game
{
	class Room
	{
	public:
		virtual bool init() = 0;
		virtual bool go();
		virtual bool shutdown();

		float getTimeStepSeconds();

	protected:
		virtual bool render();
		virtual bool update();
		virtual bool shouldExit();

	protected:
		void onUpdateStart();
		void onUpdateEnd( uint32_t timeStepMilliseconds );

		uint64_t updateStartMilliseconds;
	};
}

#endif