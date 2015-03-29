#include "MainRoom.h"
#include "core/Assert.h"
#include "draw/Draw.h"
#include "draw/ColourConstants.h"
#include "tween/TweenFactory.h"

bool MainRoom::init()
{
	VALIDATE( button.init() );

	USE_COMPONENT( button, component::Texture, setTexturePath( "textures/button.png" ) );
	USE_COMPONENT( button, component::Position, set( 100.0f, 100.0f ) );

	return true;
}

bool MainRoom::shutdown()
{
	VALIDATE( button.shutdown() );
	VALIDATE( Room::shutdown() );
	return true;
}

bool MainRoom::update()
{
	VALIDATE( Room::update() );

	float timeStep = getTimeStepSeconds();
	VALIDATE( button.update( timeStep ) );

	return true;
}

bool MainRoom::render()
{
	VALIDATE( draw::Draw::get().clear( 0xFF333333 ) );

	VALIDATE( button.render() );

	VALIDATE( draw::Draw::get().flip() );
	return true;
}