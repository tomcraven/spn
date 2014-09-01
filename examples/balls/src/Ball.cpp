#include "Ball.h"

#include "core/Assert.h"
#include "draw/Draw.h"

Ball::Ball() : incrementFrame( false )
{
	attach( &r );
	attach( &w );
	attach( &v );
}

bool Ball::init()
{
	CHECK( ComponentEntity::init() );

	t.setTexturePath( "assets/circle_sheet.png" );

	const uint32_t kFrameWidth = 16;
	const uint32_t kFrameHeight = 16;
	r.setFrameDimensions( kFrameWidth, kFrameHeight );
	
	v.x = 100.0f - ( float( rand() % 1000 ) / 1000.0f * 200.0f );
	v.y = 100.0f - ( float( rand() % 1000 ) / 1000.0f * 200.0f );
	
	p.x = float( rand() % 1000 ) / 1000.0f * ( draw::Draw::get().getScreenWidth() - kFrameWidth );
	p.y = float( rand() % 1000 ) / 1000.0f * ( draw::Draw::get().getScreenHeight() - kFrameHeight );

	return true;
}

bool Ball::render()
{
	CHECK( r.render( p ) );
	return true;
}

bool Ball::onWindowTouch( bool left, bool right, bool top, bool bottom )
{
	if ( left || right )
	{
		incrementFrame = true;
		v.x *= -1;
	}

	if ( top || bottom )
	{
		incrementFrame = true;
		v.y *= -1;
	}

	return true;
}

bool Ball::shouldIncrementFrame()
{
	if ( incrementFrame )
	{
		incrementFrame = false;
		return true;
	}
	else
	{
		return false;
	}
}