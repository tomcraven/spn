#ifndef GAME_IROOM_H
#define GAME_IROOM_H

#include "core/Types.h"

namespace component
{
	class ComponentEntity;
}

namespace game
{
	class IRoom
	{
	public:
		virtual bool init() = 0;
		virtual bool go() = 0;
		virtual bool shutdown() = 0;

	protected:
		virtual bool update();

	protected:
		void onUpdateStart();
		void onUpdateEnd( uint32_t timeStepMilliseconds );

		uint64_t updateStartMilliseconds;
	};
}

#endif