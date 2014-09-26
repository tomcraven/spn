#include "PlayTimer.h"
#include "core/Assert.h"
#include "draw/Draw.h"
#include "draw/Colour.h"

#include <limits>

namespace
{
	class NullExpiredListener : public PlayTimer::IExpiredListener
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

PlayTimer::PlayTimer() :
	timeoutSeconds( -1.0f ), 
	timeUntilTimeoutSeconds( -1.0f ), 
	shouldRepeat( false ),
	id( generateTimerId() )
{
}

bool PlayTimer::init( float inTimeoutSeconds, bool repeat )
{
	setListener( 0 );

	timeUntilTimeoutSeconds = inTimeoutSeconds;
	timeoutSeconds = inTimeoutSeconds;
	shouldRepeat = repeat;

	updateFunction = &PlayTimer::updateTimer;

	return true;
}

bool PlayTimer::update( float timeStep )
{
	CHECK( (this->*updateFunction)( timeStep ) );
	return true;
}

bool PlayTimer::nullUpdate( float timeStep )
{
	return true;
}

bool PlayTimer::updateTimer( float timeStep )
{
	timeUntilTimeoutSeconds -= timeStep;

	if ( timeUntilTimeoutSeconds <= 0 )
	{
		listener->onTimerExpired( id );
		
		timeUntilTimeoutSeconds = timeoutSeconds;

		if ( !shouldRepeat )
		{
			timeUntilTimeoutSeconds = 0;
			updateFunction = &PlayTimer::nullUpdate;
		}
	}

	return true;
}

bool PlayTimer::render()
{
	draw::Draw& draw = draw::Draw::get();
	static uint32_t screenWidth = draw.getScreenWidth();
	static uint32_t halfScreenWidth = screenWidth / 2;

	float factor = ( timeUntilTimeoutSeconds / timeoutSeconds );
	float width = screenWidth * factor;
	float leftPosition = halfScreenWidth - ( halfScreenWidth * factor );
	
	if ( factor > 0.5f )
	{
		uint8_t red = uint8_t( ( 2 * ( 1.0f - factor ) ) * 0xFF );

		draw.setColour( draw::colour::colourFromRGBA( red, 0xFF, 0 ) );
	}
	else
	{
		uint8_t green = uint8_t( ( 2 * factor ) * 0xFF );

		draw.setColour( draw::colour::colourFromRGBA( 0xFF, green, 0 ) );
	}

	draw.filledRect( leftPosition, 0, width, 10 );
	draw.setColour( draw::colour::kDefault );

	return true;
}

uint32_t PlayTimer::getId()
{
	return id;
}

void PlayTimer::setListener( PlayTimer::IExpiredListener* inListener )
{
	static NullExpiredListener nullExpiredListener;
	if ( inListener )
	{
		listener = inListener;
	}
	else
	{
		listener = &nullExpiredListener;
	}
}