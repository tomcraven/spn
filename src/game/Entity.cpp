#include "game\Entity.h"

namespace game
{
	bool Entity::init()
	{
		return true;
	}

	bool Entity::update( float timeStep )
	{
		return true;
	}

	bool Entity::render()
	{
		return true;
	}

	bool Entity::onWindowExit( bool left, bool right, bool top, bool bottom )
	{
		return true;
	}
	
	bool Entity::onWindowTouch( bool left, bool right, bool top, bool bottom )
	{
		return true;
	}

	bool Entity::onInputConsumerButtonDown( uint32_t x, uint32_t y )
	{
		return true;
	}

	bool Entity::onClickableConsumerClick()
	{
		return true;
	}

	bool Entity::shouldIncrementFrame()
	{
		return false;
	}
}