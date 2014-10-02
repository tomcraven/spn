#include "PlayTimer.h"
#include "core/Assert.h"
#include "draw/Draw.h"
#include "draw/Colour.h"
#include "draw/ScopedColour.h"

PlayTimer::PlayTimer() : timeoutProgress( 0.0f )
{
}

bool PlayTimer::update( float timeStep )
{
	CHECK( component::ComponentEntity::update( timeStep ) );
	CHECK( async::Timer::update( timeStep ) );
	return true;
}

bool PlayTimer::render()
{
	draw::Draw& draw = draw::Draw::get();
	uint32_t screenWidth = draw.getScreenWidth();
	uint32_t halfScreenWidth = screenWidth / 2;

	float width = screenWidth * timeoutProgress;
	float leftPosition = halfScreenWidth - ( halfScreenWidth * timeoutProgress );
	uint32_t colour = 0;

	if ( timeoutProgress > 0.5f )
	{
		uint8_t red = uint8_t( ( 2 * ( 1.0f - timeoutProgress ) ) * 0xFF );
		colour = draw::colour::colourFromRGBA( red, 0xFF, 0 );
	}
	else
	{
		uint8_t green = uint8_t( ( 2 * timeoutProgress ) * 0xFF );
		colour = draw::colour::colourFromRGBA( 0xFF, green, 0 );
	}

	draw::ScopedColour scopedColour( colour );
	draw.filledRect( leftPosition, 0, width, 10 );

	return true;
}

bool PlayTimer::onTimerProgress( float progress )
{
	timeoutProgress = progress;
	return true;
}