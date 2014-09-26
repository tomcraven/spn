#include "MenuRoom.h"
#include "core/Assert.h"
#include "draw/Colour.h"
#include "draw/Draw.h"

MenuRoom::MenuRoom() : menuSelection( kUnknown )
{
}

bool MenuRoom::init()
{
	CHECK( initialiseAndPlaceButton( playButton, "assets/play_button.png", 20.0f, 20.0f ) );
	CHECK( initialiseAndPlaceButton( exitButton, "assets/exit_button.png", 20.0f, 100.0f ) );

	return true;
}

bool MenuRoom::shutdown()
{
	playButton.shutdown();
	exitButton.shutdown();

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

	return true;
}

bool MenuRoom::render()
{
	CHECK( draw::Draw::get().clear( draw::colour::kLightBlue ) );
	
	CHECK( playButton.render() );
	CHECK( exitButton.render() );

	CHECK( draw::Draw::get().flip() );
	return true;
}

bool MenuRoom::update()
{
	CHECK( Room::update() );
	
	CHECK( playButton.update( getTimeStepSeconds() ) );
	CHECK( exitButton.update( getTimeStepSeconds() ) );

	return true;
}

bool MenuRoom::shouldExit()
{
	return Room::shouldExit() || hasMadeMenuSelection();
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
	
	component::Position* position = button.getComponent< component::Position >();
	position->set( x, y );

	component::Texture* texture = button.getComponent< component::Texture >();
	texture->setTexturePath( filename );

	return true;
}