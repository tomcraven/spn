#include "MainRoom.h"
#include "core/Assert.h"
#include "draw/Draw.h"
#include "draw/Colour.h"

bool MainRoom::init()
{
	VALIDATE( draw::Draw::get().rescale( 2.0f ) );
	
	ParalaxPane::Config p1 = { "textures/p1.png", true, false };
	p1.startingPosition.set( 0.0f, draw::Draw::get().inverseScaleValue( 75.0f ) );
	p1.velocity.set( -25.0f, 0.0f );
	
	ParalaxPane::Config p2 = { "textures/p1.png", true, false };
	p2.startingPosition.set( 20.0f, draw::Draw::get().inverseScaleValue( 95.0f ) );
	p2.velocity.set( -15.0f, 0.0f );

	ParalaxPane::Config* paralaxConifg[] = {
		&p1,
		&p2,
		0
	};
	VALIDATE( paralax.init( paralaxConifg ) );

	VALIDATE( city.init( 20 ) );

	return true;
}

bool MainRoom::shutdown()
{
	VALIDATE( paralax.shutdown() );
	VALIDATE( city.shutdown() );
	return true;
}

bool MainRoom::update()
{
	float timeStepSeconds = getTimeStepSeconds();
	VALIDATE( paralax.update( timeStepSeconds ) );
	VALIDATE( city.update( timeStepSeconds ) );
	return true;
}

bool MainRoom::render()
{
	VALIDATE( draw::Draw::get().clear( draw::colour::colourFromRGBA( 40, 85, 204 ) ) );

	VALIDATE( paralax.render() );
	VALIDATE( city.render() );

	VALIDATE( draw::Draw::get().flip() );
	return true;
}