#ifndef MAINROOM_H
#define MAINROOM_H

#include "game/Room.h"
#include "game/Button.h"
#include "Ball.h"
#include "PlayTimer.h"
#include "BallManager.h"

class MainRoom : public game::Room, public game::Button::Consumer, public PlayTimer::IExpiredListener
{
public:
	MainRoom();

public: // game::IRoom
	virtual bool init();
	virtual bool shutdown();
	virtual bool update();
	virtual bool render();
	virtual bool shouldExit();
	
public: // game::Button::Consumer
	virtual bool onButtonConsumerClick( uint32_t id );

public: // PlayTimer::IExpiredListener
	virtual bool onTimerExpired( uint32_t id );

private:
	friend class BallManager;

	bool createExitButton();
	
	bool onEndOfGame();

	bool initialisePlayTimer();

	bool updateInGame();
	bool updateEndGame();
	bool updateClickedBallCountBuffer();

	bool renderInGame();
	bool renderEndGame();
	bool renderFadeOut();
	bool renderScore();
	uint32_t fadeOutColour;
	uint32_t fadeOutAlpha;

	bool ( MainRoom::*renderFunction )();
	bool ( MainRoom::*updateFunction )();

	BallManager ballManager;

	PlayTimer playTimer;

	bool flagShouldExit;

	game::Button exitButton;
};

#endif