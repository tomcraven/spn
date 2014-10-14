#include "MainRoom.h"
#include "core/Algorithm.h"
#include "core/Assert.h"
#include "core/Time.h"
#include "draw/Draw.h"
#include "draw/Colour.h"
#include "draw/ScopedColour.h"

#include "component/Position.h"

namespace
{
	const uint32_t kNumBalls = 1;
}

MainRoom::MainRoom() :
	flagShouldExit( false ),
	ballManager( this ),
	fadeOut( 0, 0.3f ),
	fadeIn( 0, 0.3f )
{
}

bool MainRoom::init()
{
	CHECK( draw::Draw::get().rescale( 2.0f ) );
	
	CHECK( ballManager.init( kNumBalls ) );
	CHECK( initialisePlayTimer() );
	CHECK( createExitButton() );
	CHECK( fadeOut.setConsumer( this ) );
	CHECK( fadeIn.start() );

	return true;
}

bool MainRoom::shutdown()
{
	CHECK( ballManager.shutdown() );
	CHECK( playTimer.shutdown() );
	return true;
}

bool MainRoom::update()
{
	CHECK( Room::update() );
	
	float timeStepSeconds = getTimeStepSeconds();
	
	CHECK( ballManager.update( timeStepSeconds ) );	
	CHECK( playTimer.update( timeStepSeconds ) );
	CHECK( exitButton.update( timeStepSeconds ) );
	CHECK( fadeOut.update( timeStepSeconds ) );
	CHECK( fadeIn.update( timeStepSeconds ) );

	return true;
}

bool MainRoom::render()
{
	draw::Draw& draw = draw::Draw::get();

	CHECK( draw.clear( draw::colour::kLightBlue ) );
	CHECK( renderScore() );
	CHECK( playTimer.render() );
	CHECK( ballManager.render() );
	CHECK( exitButton.render() );
	CHECK( fadeOut.render() );
	CHECK( fadeIn.render() );

	CHECK( draw.flip() );

	return true;
}

bool MainRoom::renderScore()
{
	draw::ScopedColour scopedColour( 0xFF000000 );
	
	draw::Draw& draw = draw::Draw::get();

	const char* clickedBallsString = ballManager.getNumClickedBallsString();

	uint32_t textHeight = draw.getTextHeight();
	uint32_t textWidth = draw.getTextWidth( clickedBallsString );

	float xPosition = static_cast< float >( ( draw.getScreenWidth() / 2 ) - ( textWidth / 2 ) );
	float yPosition = static_cast< float >( ( draw.getScreenHeight() / 2 ) - ( textHeight / 2 ) );

	draw.text( clickedBallsString, xPosition, yPosition );

	return true;
}

bool MainRoom::shouldExit()
{
	return Room::shouldExit() || flagShouldExit;
}

bool MainRoom::onButtonConsumerClick( uint32_t id )
{
	if ( id == exitButton.getId() )
	{
		CHECK( onEndOfGame() );
	}

	return true;
}

bool MainRoom::onTimerExpired( uint32_t id )
{
	CHECK( id == playTimer.getId() );
	CHECK( onEndOfGame() );
	return true;
}

bool MainRoom::onTransitionComplete( uint32_t transitionId )
{
	flagShouldExit = true;
	return true;
}

bool MainRoom::onEndOfGame()
{
	CHECK( fadeOut.start() );
	return true;
}

bool MainRoom::initialisePlayTimer()
{
	playTimer.setTimeout( 30.0f );
	playTimer.setRepeat( false );
	playTimer.setTimerExpiredListener( this );

	return true;
}

bool MainRoom::createExitButton()
{
	CHECK( exitButton.init() );
	exitButton.setConsumer( this );

	USE_COMPONENT( exitButton, component::Texture, setTexturePath( "assets/exit_main_game.png" ) );
	
	component::Dimensions* dimensions;
	CHECK( exitButton.getComponent< component::Dimensions >( &dimensions ) );
	float yPosition = static_cast< float >( draw::Draw::get().getScreenHeight() - dimensions->height );
	float xPosition = static_cast< float >( draw::Draw::get().getScreenWidth() - dimensions->width );
	USE_COMPONENT( exitButton, component::Position, set( xPosition, yPosition ) );

	return true;
}