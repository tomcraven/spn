#include "component/WindowTouchCollision.h"
#include "component/ComponentEntity.h"
#include "component/Position.h"
#include "component/RenderSheet.h"
#include "component/RenderTexture.h"
#include "component/Dimensions.h"
#include "core/Assert.h"
#include "draw/Draw.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	bool WindowTouchCollision::initComponent( ComponentEntity* entity )
	{
		VALIDATE( entity->getComponent< Position >( &p ) );
		VALIDATE( entity->getComponent< Dimensions >( &d ) );
		
		return true;
	}

	bool WindowTouchCollision::update( ComponentEntity* entity, float timeStep )
	{
		uint32_t width = d->width;
		uint32_t height = d->height;
		
		uint32_t screenWidth = draw::Draw::get().getScreenWidth();
		uint32_t screenHeight = draw::Draw::get().getScreenHeight();

		bool left = p->x < 0;
		bool right = p->x + width > screenWidth;
		bool top = p->y < 0;
		bool bottom = p->y + height > screenHeight;

		if ( left || right || top || bottom )
		{
			VALIDATE( entity->onWindowTouch( left, right, top, bottom ) );
		}

		return true;
	}

	uint32_t WindowTouchCollision::getType()
	{
		return typeId;
	}
} // component