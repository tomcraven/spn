#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "core/Types.h"
#include "component/Clickable.h"
#include "input/Input.h"

namespace game
{
	class Entity : public input::Input::Consumer
	{
	public:
		virtual bool init();
		virtual bool shutdown();
		virtual bool update( float timeStep );
		virtual bool render();
		
		virtual bool onWindowTouch( bool left, bool right, bool top, bool bottom );

		virtual bool shouldIncrementFrame();

	public: // input::Input::Consumer
		virtual bool onInputConsumerButtonDown( uint32_t x, uint32_t y );
	};
}

#endif