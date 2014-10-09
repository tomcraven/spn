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
	const uint32_t kNumBalls = 10;
}

MainRoom::MainRoom() :
	updateFunction( &MainRoom::updateInGame ),
	renderFunction( &MainRoom::renderInGame ),
	fadeOutAlpha( 0 ),
	fadeOutColour( draw::colour::kLightBlue ^ 0xFF000000 ),
	flagShouldExit( false ),
	ballManager( this )
{
}

bool MainRoom::init()
{
	CHECK( draw::Draw::get().rescale( 2.0f ) );
	
	CHECK( ballManager.init( kNumBalls ) );
	CHECK( initialisePlayTimer() );
	CHECK( createExitButton() );

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
	CHECK( ( this->*updateFunction )() );

	return true;
}

bool MainRoom::updateInGame()
{
	CHECK( Room::update() );
	
	float timeStepSeconds = getTimeStepSeconds();
	
	CHECK( ballManager.update( timeStepSeconds ) );	
	CHECK( playTimer.update( timeStepSeconds ) );
	CHECK( exitButton.update( timeStepSeconds ) );

	return true;
}

bool MainRoom::updateEndGame()
{
	CHECK( Room::update() );
	
	float timeStepSeconds = getTimeStepSeconds();
	CHECK( ballManager.update( timeStepSeconds ) );	
	
	const uint32_t kMaxFadeOutValue = 0xFF;
	if ( fadeOutAlpha >= kMaxFadeOutValue )
	{
		flagShouldExit = true;
	}
	else
	{
		const float kFadeOutTimeSeconds = 0.5f;
		float alphaIncrement = kMaxFadeOutValue * ( getTimeStepSeconds() / kFadeOutTimeSeconds );
		fadeOutAlpha += static_cast< uint32_t >( alphaIncrement );

		fadeOutAlpha = core::algorithm::clamp( fadeOutAlpha, 0u, kMaxFadeOutValue );
	}

	return true;
}

bool MainRoom::render()
{
	CHECK( ( this->*renderFunction )() );
	return true;
}

bool MainRoom::renderInGame()
{
	draw::Draw& draw = draw::Draw::get();

	CHECK( draw.clear( draw::colour::kLightBlue ) );
	CHECK( renderScore() );
	CHECK( playTimer.render() );
	CHECK( ballManager.render() );
	CHECK( exitButton.render() );

	CHECK( draw.flip() );
	return true;
}

bool MainRoom::renderEndGame()
{
	draw::Draw& draw = draw::Draw::get();

	CHECK( draw.clear( draw::colour::kLightBlue ) );
	CHECK( renderScore() );
	CHECK( playTimer.render() );
	CHECK( ballManager.render() );
	CHECK( exitButton.render() );
	CHECK( renderFadeOut() );

	CHECK( draw.flip() );
	return true;
}

bool MainRoom::renderFadeOut()
{
	draw::ScopedColour scopedColour( fadeOutColour | ( fadeOutAlpha << 24 ) );

	draw::Draw& draw = draw::Draw::get();
	static float screenWidth = static_cast< float >( draw.getScreenWidth() );
	static float screenHeight = static_cast< float >( draw.getScreenHeight() );

	draw.filledRect( 0.0f, 0.0f, screenWidth, screenHeight );

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

bool MainRoom::onEndOfGame()
{
	renderFunction = &MainRoom::renderEndGame;
	updateFunction = &MainRoom::updateEndGame;

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