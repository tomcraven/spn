#ifndef BALL_H
#define BALL_H

#include "component/ComponentEntity.h"
#include "component/Position.h"
#include "component/RenderSheetCustom.h"
#include "component/RenderTexture.h"
#include "component/Velocity.h"
#include "component/WindowTouchCollision.h"
#include "component/Dimensions.h"
#include "game/Button.h"

#include <stdlib.h>

class Ball : public game::Button
{
public:
	Ball();
	bool init();
	bool render();
	bool onWindowTouch( bool left, bool right, bool top, bool bottom );
	bool shouldIncrementFrame();

private:
	component::RenderSheetCustom r;
	component::Velocity v;
	component::WindowTouchCollision w;

	bool incrementFrame;
};

#endif