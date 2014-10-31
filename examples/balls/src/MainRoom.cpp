#include "MainRoom.h"
#include "core/Algorithm.h"
#include "core/Assert.h"
#include "core/Time.h"
#include "draw/Draw.h"
#include "draw/Colour.h"
#include "draw/ScopedColour.h"
#include "component/Position.h"
#include "tween/TweenFactory.h"

namespace
{
	const uint32_t kNumBalls = 10;
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
	VALIDATE( draw::Draw::get().rescale( 2.0f ) );
	
	VALIDATE( ballManager.init( kNumBalls ) );
	VALIDATE( initialisePlayTimer() );
	VALIDATE( createExitButton() );
	VALIDATE( fadeOut.setConsumer( this ) );
	VALIDATE( fadeIn.start() );

	using namespace tween;
	TweenFactory::get().create( 
		&playTimer.getComponent< component::Position >()->y,
		FROM, -10.0f,
		TO, 0.0f,
		LINEAR,
		OVER, 0.2f, SECONDS,
		DELAYED_BY, 0.2f, SECONDS,
		END );

	return true;
}

bool MainRoom::shutdown()
{
	VALIDATE( Room::shutdown() );
	VALIDATE( ballManager.shutdown() );
	VALIDATE( playTimer.shutdown() );
	return true;
}

bool MainRoom::update()
{
	VALIDATE( Room::update() );
	
	float timeStepSeconds = getTimeStepSeconds();
	
	VALIDATE( ballManager.update( timeStepSeconds ) );	
	VALIDATE( playTimer.update( timeStepSeconds ) );
	VALIDATE( exitButton.update( timeStepSeconds ) );
	VALIDATE( fadeOut.update( timeStepSeconds ) );
	VALIDATE( fadeIn.update( timeStepSeconds ) );

	return true;
}

bool MainRoom::render()
{
	draw::Draw& draw = draw::Draw::get();

	VALIDATE( draw.clear( draw::colour::kLightBlue ) );
	VALIDATE( renderScore() );
	VALIDATE( playTimer.render() );
	VALIDATE( ballManager.render() );
	VALIDATE( exitButton.render() );
	VALIDATE( fadeOut.render() );
	VALIDATE( fadeIn.render() );

	VALIDATE( draw.flip() );

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
		VALIDATE( onEndOfGame() );
	}

	return true;
}

bool MainRoom::onTimerExpired( uint32_t id )
{
	VALIDATE( id == playTimer.getId() );
	VALIDATE( onEndOfGame() );
	return true;
}

bool MainRoom::onTransitionComplete( uint32_t transitionId )
{
	flagShouldExit = true;
	return true;
}

bool MainRoom::onEndOfGame()
{
	VALIDATE( fadeOut.start() );
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
	VALIDATE( exitButton.init() );
	exitButton.setConsumer( this );

	USE_COMPONENT( exitButton, component::Texture, setTexturePath( "textures/exit_main_game.png" ) );
	
	component::Dimensions* dimensions;
	float screenWidthFloat = static_cast< float >( draw::Draw::get().getScreenWidth() );
	VALIDATE( exitButton.getComponent< component::Dimensions >( &dimensions ) );
	float yPosition = static_cast< float >( draw::Draw::get().getScreenHeight() - dimensions->height );
	float xPosition = screenWidthFloat;
	USE_COMPONENT( exitButton, component::Position, set( xPosition, yPosition ) );

	using namespace tween;
	TweenFactory::get().create(
		&exitButton.getComponent< component::Position >()->x,
		FROM, screenWidthFloat,
		TO, screenWidthFloat - dimensions->width,
		LINEAR,
		OVER, 0.2f, SECONDS,
		DELAYED_BY, 0.2f, SECONDS,
		END );

	return true;
}