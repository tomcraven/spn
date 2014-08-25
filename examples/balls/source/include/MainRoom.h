#ifndef MAINROOM_H
#define MAINROOM_H

#include "game/Room.h"
#include "Ball.h"

class MainRoom : public game::Room
{
public: // game::IRoom
	virtual bool init();
	virtual bool shutdown();
	virtual bool update();
	virtual bool render();

private:
	Ball* balls;
};

#endif