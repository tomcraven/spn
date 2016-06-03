#ifndef MAINROOM_H
#define MAINROOM_H

#include "game/Room.h"
#include "Parallax.h"
#include "City.h"

class MainRoom : public game::Room
{
public: // game::Room
	virtual bool init();
	virtual bool shutdown();
	virtual bool update();
	virtual bool render();

private:
	Parallax parallax;
	City city;
};

#endif
