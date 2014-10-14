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
	CHECK( draw::Draw::get().rescale( 1.0f ) );

	CHECK( initialiseAndPlaceButton( playButton, "assets/play_button.png", 20.0f, 20.0f ) );
	CHECK( initialiseAndPlaceButton( exitButton, "assets/exit_button.png", 20.0f, 100.0f ) );

	CHECK( fadeIn.start() );
	CHECK( fadeOut.setConsumer( this ) );

	return true;
}

bool MenuRoom::shutdown()
{
	CHECK( playButton.shutdown() );
	CHECK( exitButton.shutdown() );

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

	CHECK( fadeOut.start() );

	return true;
}

bool MenuRoom::onTransitionComplete( uint32_t transitionId )
{
	flagFadeOutHasFinished = true;
	return true;
}

bool MenuRoom::render()
{
	CHECK( draw::Draw::get().clear( draw::colour::kLightBlue ) );
	
	CHECK( playButton.render() );
	CHECK( exitButton.render() );
	CHECK( fadeIn.render() );
	CHECK( fadeOut.render() );

	CHECK( draw::Draw::get().flip() );
	return true;
}

bool MenuRoom::update()
{
	CHECK( Room::update() );

	float timeStepSeconds = getTimeStepSeconds();
	
	CHECK( playButton.update( timeStepSeconds ) );
	CHECK( exitButton.update( timeStepSeconds ) );
	CHECK( fadeIn.update( timeStepSeconds ) );
	CHECK( fadeOut.update( timeStepSeconds ) );

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
	CHECK( button.init() );
	button.setConsumer( this );
	USE_COMPONENT( button, component::Position, set( x, y ) );
	USE_COMPONENT( button, component::Texture, setTexturePath( filename ) );

	return true;
}