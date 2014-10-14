#ifndef MENUROOM_H
#define MENUROOM_H

#include "game/Room.h"
#include "game/Button.h"
#include "game/Transition/FadeIn.h"
#include "game/Transition/FadeOut.h"

class MenuRoom : 
	public game::Room, 
	public game::Button::Consumer,
	public game::transition::ITransition::IConsumer
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
	virtual bool shutdown();
	virtual bool render();
	virtual bool update();
	virtual bool shouldExit();

public: // game::Button::Consumer
	virtual bool onButtonConsumerClick( uint32_t id );

public: // game::transition::ITransition::IConsumer
	virtual bool onTransitionComplete( uint32_t transitionId );

private:
	bool hasMadeMenuSelection();
	bool initialiseAndPlaceButton( game::Button& button, const char* filename, float x, float y );
	
	game::Button playButton;
	game::Button exitButton;

	MenuSelection menuSelection;
	
	game::transition::FadeIn fadeIn;
	game::transition::FadeOut fadeOut;

	bool flagFadeOutHasFinished;
};

#endif