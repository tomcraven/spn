#ifndef MENUROOM_H
#define MENUROOM_H

#include "game/Room.h"
#include "game/Button.h"

class MenuRoom : public game::Room, game::Button::Consumer
{
public:
	MenuRoom();

	enum MenuSelection
	{
		kPlay,
		kExit,

		kUnknown
	};

	MenuSelection getMenuSelection();

public: // game::Room
	virtual bool init();
	virtual bool render();
	virtual bool update();
	virtual bool shouldExit();

public: // game::Button::Consumer
	virtual bool onButtonConsumerClick( uint32_t id );

private:
	bool hasMadeMenuSelection();
	bool initialiseAndPlaceButton( game::Button& button, const char* filename, float x, float y );
	
	game::Button playButton;
	game::Button exitButton;

	MenuSelection menuSelection;
};

#endif