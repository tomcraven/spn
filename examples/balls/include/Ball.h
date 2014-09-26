#ifndef BALL_H
#define BALL_H

#include "component/Velocity.h"
#include "component/WindowTouchCollision.h"
#include "game/Button.h"

class Ball : public game::Button
{
public:
	Ball();
	bool init();
	bool render();
	bool onWindowTouch( bool left, bool right, bool top, bool bottom );

private:
	component::Velocity v;
	component::WindowTouchCollision w;

	uint32_t colour;
};

#endif