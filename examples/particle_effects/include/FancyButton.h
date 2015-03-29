#ifndef FANCYBUTTON_H
#define FANCYBUTTON_H

#include "game/Button.h"
#include "emitter/Emitter.h"

class FancyButton : public game::Button
{
public:
	bool init();
	bool shutdown();
	virtual bool render();
	virtual bool update( float timeStep );

	Emitter emitter;
};

#endif