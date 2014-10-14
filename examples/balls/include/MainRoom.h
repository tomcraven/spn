#ifndef MAINROOM_H
#define MAINROOM_H

#include "game/Room.h"
#include "game/Button.h"
#include "game/transition/FadeOut.h"
#include "game/transition/FadeIn.h"
#include "Ball.h"
#include "PlayTimer.h"
#include "BallManager.h"

class MainRoom : 
	public game::Room, 
	public game::Button::Consumer, 
	public PlayTimer::IExpiredListener,
	public game::transition::ITransition::IConsumer
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

public: // game::ITransition::IConsumer
	virtual bool onTransitionComplete( uint32_t transitionId );

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
	bool renderScore();

	BallManager ballManager;

	PlayTimer playTimer;

	bool flagShouldExit;

	game::Button exitButton;

	game::transition::FadeOut fadeOut;
	game::transition::FadeIn fadeIn;
};

#endif