#include "Ball.h"

#include "core/Assert.h"
#include "draw/Colour.h"
#include "draw/Draw.h"
#include "draw/ScopedColour.h"

Ball::Ball()
{
	attach( &w );
	attach( &v );
}

bool Ball::init()
{
	VALIDATE( ComponentEntity::init() );

	t.setTexturePath( "textures/circle_white.png" );

	v.x = 100.0f - ( float( rand() % 1000 ) / 1000.0f * 200.0f );
	v.y = 100.0f - ( float( rand() % 1000 ) / 1000.0f * 200.0f );

	const uint32_t kFrameWidth = t.getWidth();
	const uint32_t kFrameHeight = t.getHeight();
	p.x = float( rand() % 1000 ) / 1000.0f * ( draw::Draw::get().getScreenWidth() - kFrameWidth );
	p.y = float( rand() % 1000 ) / 1000.0f * ( draw::Draw::get().getScreenHeight() - kFrameHeight );

	colour = draw::colour::colourFromRGBA(
		rand() % 255,
		rand() % 255,
		rand() % 255);

	return true;
}

bool Ball::render()
{
	draw::ScopedColour scopedColour( colour );
	VALIDATE( r.render( p ) );

	return true;
}

bool Ball::onWindowTouch( bool left, bool right, bool top, bool bottom )
{
	if ( left || right )
	{
		v.x *= -1;
	}

	if ( top || bottom )
	{
		v.y *= -1;
	}

	return true;
}