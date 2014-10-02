#include "async/Timer.h"
#include "core/Assert.h"

namespace
{
	class NullExpiredListener : public async::Timer::IExpiredListener
	{
	public: // PlayTimer::IExpiredListener
		virtual bool onTimerExpired( uint32_t id )
		{
			return true;
		}
	};

	uint32_t generateTimerId()
	{
		static uint32_t id = 0;
		return id++;
	}
}

namespace async
{
	Timer::Timer() :
		timeUntilTimeoutSeconds( -1.0f ),
		timeoutSeconds( -1.0f ),
		flagShouldRepeat( false ),
		updateFunction( &Timer::updateNull ),
		id( generateTimerId() )
	{
		setTimerExpiredListener( 0 );
	}
	
	void Timer::setTimeout( float inTimeoutSeconds )
	{
		timeoutSeconds = inTimeoutSeconds;
		timeUntilTimeoutSeconds = inTimeoutSeconds;

		if ( inTimeoutSeconds > 0.0f )
		{
			updateFunction = &Timer::updateTimer;
		}
	}

	void Timer::setRepeat( bool shouldRepeat )
	{
		flagShouldRepeat = shouldRepeat;
	}

	bool Timer::update( float timeStep )
	{
		CHECK( (this->*updateFunction)( timeStep ) );
		return true;
	}

	bool Timer::updateNull( float timeStep )
	{
		return true;
	}

	bool Timer::updateTimer( float timeStep )
	{
		timeUntilTimeoutSeconds -= timeStep;

		if ( timeUntilTimeoutSeconds <= 0 )
		{
			listener->onTimerExpired( id );
		
			timeUntilTimeoutSeconds = timeoutSeconds;

			if ( !flagShouldRepeat )
			{
				timeUntilTimeoutSeconds = 0;
				updateFunction = &Timer::updateNull;
			}
		}

		CHECK( onTimerProgress( timeUntilTimeoutSeconds / timeoutSeconds ) );

		return true;
	}

	uint32_t Timer::getId()
	{
		return id;
	}

	void Timer::setTimerExpiredListener( Timer::IExpiredListener* inListener )
	{
		if ( inListener )
		{
			listener = inListener;
		}
		else
		{
			static NullExpiredListener nullExpiredListener;
			listener = &nullExpiredListener;
		}
	}

	bool Timer::onTimerProgress( float progress )
	{
		return true;
	}
}