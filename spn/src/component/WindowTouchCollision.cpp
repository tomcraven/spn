#include "component/WindowTouchCollision.h"
#include "component/ComponentEntity.h"
#include "component/Position.h"
#include "component/IRender.h"
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
	bool WindowTouchCollision::init( ComponentEntity* entity )
	{
		CHECK( entity->getComponent< Position >( &p ) );
		CHECK( entity->getComponent< Dimensions >( &d ) );
		
		screenWidth = draw::Draw::get().getScreenWidth();
		screenHeight = draw::Draw::get().getScreenHeight();

		return true;
	}

	bool WindowTouchCollision::update( ComponentEntity* entity, float timeStep )
	{
		uint32_t width = d->width;
		uint32_t height = d->height;

		bool left = p->x < 0;
		bool right = p->x + width > screenWidth;
		bool top = p->y < 0;
		bool bottom = p->y + height > screenHeight;

		if ( left || right || top || bottom )
		{
			CHECK( entity->onWindowTouch( left, right, top, bottom ) );
		}

		return true;
	}

	uint32_t WindowTouchCollision::getType()
	{
		return typeId;
	}
} // component