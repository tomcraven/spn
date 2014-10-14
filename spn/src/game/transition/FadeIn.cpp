#include "game/transition/FadeIn.h"
#include "core/Algorithm.h"
#include "core/Assert.h"
#include "draw/Draw.h"
#include "draw/ScopedColour.h"

namespace game { namespace transition
{
	FadeIn::FadeIn( uint32_t inColour, float inTimeoutSeconds ) : 
		colour( inColour ),
		fadeInAlpha( 0xFF ),
		timeoutSeconds( inTimeoutSeconds ),
		updateFunction( &FadeIn::updateNull )
	{
	}

	bool FadeIn::render()
	{
		draw::ScopedColour scopedColour( colour | ( fadeInAlpha << 24 ) );

		draw::Draw& draw = draw::Draw::get();
		static float screenWidth = static_cast< float >( draw.getScreenWidth() );
		static float screenHeight = static_cast< float >( draw.getScreenHeight() );

		draw.filledRect( 0.0f, 0.0f, screenWidth, screenHeight );
		return true;
	}

	bool FadeIn::update( float timeStepSeconds )
	{
		VALIDATE( ( this->*updateFunction )( timeStepSeconds ) );
		return true;
	}

	bool FadeIn::start()
	{
		updateFunction = &FadeIn::updateTransition;
		return true;
	}

	bool FadeIn::updateTransition( float timeStepSeconds )
	{
		uint32_t alphaDecrement = static_cast< uint32_t >( 0xFF * ( timeStepSeconds / timeoutSeconds ) );
		alphaDecrement = core::algorithm::min( alphaDecrement, fadeInAlpha );
		fadeInAlpha -= alphaDecrement;
		
		timeoutSeconds -= timeStepSeconds;
		if ( timeoutSeconds < 0 )
		{
			consumer->onTransitionComplete( id );
			
			updateFunction = &FadeIn::updateNull;
		}
		return true;
	}

	bool FadeIn::updateNull( float timeStepSeconds )
	{
		return true;
	}
}
}