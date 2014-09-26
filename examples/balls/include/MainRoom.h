#ifndef MAINROOM_H
#define MAINROOM_H

#include "game/Room.h"
#include "Ball.h"
#include "PlayTimer.h"

class MainRoom : public game::Room, public game::Button::Consumer, public PlayTimer::IExpiredListener
{
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
	bool onEndOfGame();

	bool updateInGame();
	bool updateEndGame();
	bool updateBalls( float timeStepSeconds );

	bool renderInGame();
	bool renderEndGame();
	bool renderFadeOut();
	bool renderBalls();
	uint32_t fadeOutColour;
	uint32_t fadeOutAlpha;

	bool ( MainRoom::*renderFunction )();
	bool ( MainRoom::*updateFunction )();

	Ball* freeBalls;

	typedef std::vector< Ball* > BallContainer;
	BallContainer balls;
	std::vector< BallContainer::iterator > ballsToErase;

	PlayTimer playTimer;

	bool flagShouldExit;
};

#endif