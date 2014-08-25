#include "Ball.h"

#include "core/Assert.h"
#include "draw/Draw.h"

Ball::Ball() : incrementFrame( false )
{
	attach( &p );
	attach( &r );
	attach( &v );
	attach( &w );
	attach( &d );
	attach( &t );
}

bool Ball::init()
{
	CHECK( ComponentEntity::init() );

	t.setTexturePath( "assets/circle_sheet.png" );
	r.setFrameDimensions( 16, 16 );
	
	v.x = float( rand() % 1000 ) / 1000.0f * 100.0f;
	v.y = float( rand() % 1000 ) / 1000.0f * 100.0f;

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