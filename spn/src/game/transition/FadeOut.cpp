#include "game/transition/FadeOut.h"
#include "core/Algorithm.h"
#include "core/Assert.h"
#include "draw/Draw.h"
#include "draw/ScopedColour.h"

namespace game { namespace transition
{
	FadeOut::FadeOut( uint32_t inColour, float inTimeoutSeconds ) : 
		colour( inColour ),
		fadeOutAlpha( 0 ),
		timeoutSeconds( inTimeoutSeconds ),
		updateFunction( &FadeOut::updateNull )
	{
	}

	bool FadeOut::startIn( float seconds )
	{
		delaySeconds = seconds;
		updateFunction = &FadeOut::updateDelay;
		return true;
	}

	bool FadeOut::render()
	{
		draw::ScopedColour scopedColour( colour | ( fadeOutAlpha << 24 ) );

		draw::Draw& draw = draw::Draw::get();
		static float screenWidth = static_cast< float >( draw.getScreenWidth() );
		static float screenHeight = static_cast< float >( draw.getScreenHeight() );

		draw.filledRect( 0.0f, 0.0f, screenWidth, screenHeight );
		return true;
	}

	bool FadeOut::update( float timeStepSeconds )
	{
		VALIDATE( ( this->*updateFunction )( timeStepSeconds ) );
		return true;
	}

	bool FadeOut::start()
	{
		updateFunction = &FadeOut::updateTransition;
		return true;
	}

	bool FadeOut::updateTransition( float timeStepSeconds )
	{
		uint32_t alphaIncrement = static_cast< uint32_t >( 0xFF * ( timeStepSeconds / timeoutSeconds ) );
		alphaIncrement = core::algorithm::min( 0xFFu - fadeOutAlpha, alphaIncrement );
		fadeOutAlpha += alphaIncrement;
		
		timeoutSeconds -= timeStepSeconds;
		if ( timeoutSeconds < 0 )
		{
			consumer->onTransitionComplete( id );
			
			updateFunction = &FadeOut::updateNull;
		}
		return true;
	}

	bool FadeOut::updateDelay( float timeStepSeconds )
	{
		delaySeconds -= timeStepSeconds;
		if ( delaySeconds <= 0.0f )
		{
			updateFunction = &FadeOut::updateTransition;
		}

		return true;
	}

	bool FadeOut::updateNull( float timeStepSeconds )
	{
		return true;
	}
}
}