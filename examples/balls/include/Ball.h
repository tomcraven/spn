#ifndef BALL_H
#define BALL_H

#include "component/ComponentEntity.h"
#include "component/Position.h"
#include "component/RenderSheetCustom.h"
#include "component/RenderTexture.h"
#include "component/Velocity.h"
#include "component/WindowTouchCollision.h"
#include "component/Dimensions.h"
#include "component/Texture.h"

#include <stdlib.h>

class Ball : public component::ComponentEntity
{
public:
	Ball();
	bool init();
	bool render();
	bool onWindowTouch( bool left, bool right, bool top, bool bottom );
	bool shouldIncrementFrame();

private:
	component::Position p;
	component::Dimensions d;
	component::RenderSheetCustom r;
	component::Velocity v;
	component::WindowTouchCollision w;
	component::Texture t;

	bool incrementFrame;
};

#endif