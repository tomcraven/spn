#ifndef PLAY_TIMER_H
#define PLAY_TIMER_H

#include "component/ComponentEntity.h"
#include "component/Position.h"
#include "async/Timer.h"

class PlayTimer : public component::ComponentEntity, public async::Timer
{
public:
	PlayTimer();
	bool update( float timeStep );
	bool render();

private: // async::Timer
	bool onTimerProgress( float progress );

private:
	float timeoutProgress;
};

#endif