#ifndef MAINROOM_H
#define MAINROOM_H

#include "game/Room.h"
#include "RenderTileSheet.h"
#include "Player.h"
#include "input/Input.h"
#include "NpcPopulation.h"
#include "talk/TalkDisplay.h"

class MainRoom : 
	public game::Room,
	public input::Input::Consumer
{
public: // game::Room
	virtual bool init();
	virtual bool shutdown();
	virtual bool update();
	virtual bool render();

public: // input::Input::Consumer
	virtual bool onInputConsumerButtonDown( uint32_t x, uint32_t y );

private:
	bool initLevel();
	bool initNpcPopulation();

private:
	Player player;
	component::Position* viewportCentrePosition;
	RenderTileSheet level;

	NpcPopulation npcPopulation;
	talk::TalkDisplay talkDisplay;
};

#endif