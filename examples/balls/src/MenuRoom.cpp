#include "MenuRoom.h"
#include "core/Assert.h"
#include "draw/Colour.h"
#include "draw/Draw.h"

MenuRoom::MenuRoom() : 
	menuSelection( kUnknown ),
	fadeIn( 0, 0.3f ),
	fadeOut( 0, 0.3f ),
	flagFadeOutHasFinished( false )
{
}

bool MenuRoom::init()
{
	VALIDATE( draw::Draw::get().rescale( 1.0f ) );

	VALIDATE( initialiseAndPlaceButton( playButton, "assets/play_button.png", 20.0f, 20.0f ) );
	VALIDATE( initialiseAndPlaceButton( exitButton, "assets/exit_button.png", 20.0f, 100.0f ) );

	VALIDATE( fadeIn.start() );
	VALIDATE( fadeOut.setConsumer( this ) );

	return true;
}

bool MenuRoom::shutdown()
{
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

	VALIDATE( fadeOut.start() );

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