#include "MenuRoom.h"
#include "core/Assert.h"
#include "draw/Colour.h"
#include "draw/Draw.h"
#include "tween/TweenFactory.h"

MenuRoom::MenuRoom() : 
	menuSelection( kUnknown ),
	fadeIn( 0, 0.3f ),
	fadeOut( 0, 0.3f ),
	flagFadeOutHasFinished( false )
{
}

bool MenuRoom::init()
{
	VALIDATE( draw::Draw::get().rescale( 2.0f ) );

	VALIDATE( initialiseAndPlaceButton( playButton, "textures/play_button.png", 20.0f, 20.0f ) );
	VALIDATE( initialiseAndPlaceButton( exitButton, "textures/exit_button.png", 20.0f, 100.0f ) );

	using namespace tween;
	TweenFactory::get().create( 
		&playButton.getComponent< component::Position >()->x,
		FROM, -128.0f,
		TO, 20.0f,
		TWEEN_TYPE, QUADRATIC,
		OVER, 0.5f, SECONDS,
		END );
	
	TweenFactory::get().create( 
		&exitButton.getComponent< component::Position >()->x,
		FROM, -128.0f,
		TO, 20.0f,
		TWEEN_TYPE, QUADRATIC,
		OVER, 0.5f, SECONDS,
		DELAYED_BY, 0.2f, SECONDS,
		END );
	
	TweenFactory::get().create( 
		&playButton.getComponent< component::Rotation >()->r,
		FROM, -0.05f,
		TO, 0.05f,
		TWEEN_TYPE, QUADRATIC,
		OVER, 0.5f, SECONDS,
		REPEAT, MIRROR,
		END );

	TweenFactory::get().create( 
		&exitButton.getComponent< component::Rotation >()->r,
		FROM, -0.05f,
		TO, 0.05f,
		TWEEN_TYPE, QUADRATIC,
		OVER, 0.5f, SECONDS,
		DELAYED_BY, 0.33f, SECONDS,
		REPEAT, MIRROR,
		END );

	VALIDATE( fadeIn.start() );
	VALIDATE( fadeOut.setConsumer( this ) );

	return true;
}

bool MenuRoom::shutdown()
{
	VALIDATE( Room::shutdown() );
	VALIDATE( playButton.shutdown() );
	VALIDATE( exitButton.shutdown() );

	return true;
}

bool MenuRoom::onButtonConsumerClick( uint32_t id )
{
	if ( id == playButton.getId() )
	{
		menuSelection = kPlay;
	}
	else if ( id == exitButton.getId() )
	{
		menuSelection = kExit;
	}
	else
	{
		menuSelection = kUnknown;
	}
	
	float screenWidthFloat = static_cast< float >( draw::Draw::get().getScreenWidth() );

	using namespace tween;
	TweenFactory::get().create( 
		&playButton.getComponent< component::Position >()->x,
		FROM_CURRENT,
		TO, screenWidthFloat + 10.0f,
		TWEEN_TYPE, QUADRATIC_IN,
		OVER, 0.3f, SECONDS,
		END );

	TweenFactory::get().create( 
		&exitButton.getComponent< component::Position >()->x,
		FROM_CURRENT,
		TO, screenWidthFloat + 10.0f,
		TWEEN_TYPE, QUADRATIC_IN,
		OVER, 0.3f, SECONDS,
		DELAYED_BY, 0.2f, SECONDS,
		END );

	VALIDATE( fadeOut.startIn( 0.5f ) );

	return true;
}

bool MenuRoom::onTransitionComplete( uint32_t transitionId )
{
	flagFadeOutHasFinished = true;
	return true;
}

bool MenuRoom::render()
{
	VALIDATE( draw::Draw::get().clear( draw::colour::kLightBlue ) );
	
	VALIDATE( playButton.render() );
	VALIDATE( exitButton.render() );
	VALIDATE( fadeIn.render() );
	VALIDATE( fadeOut.render() );

	VALIDATE( draw::Draw::get().flip() );
	return true;
}

bool MenuRoom::update()
{
	VALIDATE( Room::update() );

	float timeStepSeconds = getTimeStepSeconds();
	
	VALIDATE( playButton.update( timeStepSeconds ) );
	VALIDATE( exitButton.update( timeStepSeconds ) );
	VALIDATE( fadeIn.update( timeStepSeconds ) );
	VALIDATE( fadeOut.update( timeStepSeconds ) );

	return true;
}

bool MenuRoom::shouldExit()
{
	return Room::shouldExit() || ( hasMadeMenuSelection() && flagFadeOutHasFinished );
}

MenuRoom::MenuSelection MenuRoom::getMenuSelection()
{
	return menuSelection;
}

bool MenuRoom::hasMadeMenuSelection()
{
	return menuSelection != kUnknown;
}

bool MenuRoom::initialiseAndPlaceButton( game::Button& button, const char* filename, float x, float y )
{
	VALIDATE( button.init() );
	button.setConsumer( this );
	USE_COMPONENT( button, component::Position, set( x, y ) );
	USE_COMPONENT( button, component::Texture, setTexturePath( filename ) );

	return true;
}