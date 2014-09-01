#ifndef MAINROOM_H
#define MAINROOM_H

#include "game/Room.h"
#include "Ball.h"

class MainRoom : public game::Room, public game::Button::Consumer
{
public: // game::IRoom
	virtual bool init();
	virtual bool shutdown();
	virtual bool update();
	virtual bool render();
	
public: // game::Button::Consumer
	virtual bool onButtonConsumerClick( uint32_t id );

private:
	Ball* freeBalls;
	std::vector< Ball* > balls;
};

#endif