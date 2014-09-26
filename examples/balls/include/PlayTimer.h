#ifndef PLAY_TIMER_H
#define PLAY_TIMER_H

#include "component/ComponentEntity.h"
#include "component/Position.h"

class PlayTimer : public component::ComponentEntity
{
public:
	class IExpiredListener
	{
	public:
		virtual bool onTimerExpired( uint32_t id ) = 0;
	};

	PlayTimer();
	bool init( float timeoutSeconds, bool repeat = false );
	bool update( float timeStep );
	bool render();

	uint32_t getId();

	void setListener( IExpiredListener* listener );

private:
	bool nullUpdate( float timeStep );
	bool updateTimer( float timeStep );

	bool ( PlayTimer::*updateFunction )( float );

	IExpiredListener* listener;

	float timeUntilTimeoutSeconds;
	float timeoutSeconds;
	bool shouldRepeat;
	uint32_t id;
};

#endif