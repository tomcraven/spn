#ifndef ASYNC_TIMER_H
#define ASYNC_TIMER_H

#include "core/Types.h"

namespace async
{
	class Timer
	{
	public:
		class IExpiredListener
		{
		public:
			virtual bool onTimerExpired( uint32_t id ) = 0;
		};

		Timer();

		void setTimeout( float timeoutSeconds );
		void setRepeat( bool shouldRepeat );
		void setTimerExpiredListener( IExpiredListener* listener );

		bool update( float timeStep );

		uint32_t getId();

	private:
		bool updateNull( float timeStep );
		bool updateTimer( float timeStep );
		bool ( Timer::*updateFunction )( float );
		
		virtual bool onTimerProgress( float progress );

		float timeUntilTimeoutSeconds;
		float timeoutSeconds;
		bool flagShouldRepeat;
		bool hasSetTimeout;
		
		IExpiredListener* listener;

		uint32_t id;
	};
}

#endif