#ifndef MAINROOM_H
#define MAINROOM_H

#include "game/Room.h"
#include "FancyButton.h"

class MainRoom : public game::Room
{
public: // game::Room
	virtual bool init();
	virtual bool shutdown();
	virtual bool update();
	virtual bool render();

private:
	FancyButton button;
};

#endif