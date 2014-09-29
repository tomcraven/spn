#include "component/WindowExitCollision.h"
#include "component/ComponentEntity.h"
#include "component/Position.h"
#include "component/Dimensions.h"
#include "core/Assert.h"
#include "draw/Draw.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	bool WindowExitCollision::init( ComponentEntity* entity )
	{
		CHECK( entity->getComponent< Position >( &p ) );
		CHECK( entity->getComponent< Dimensions >( &d ) );

		return true;
	}

	bool WindowExitCollision::update( ComponentEntity* entity, float timeStep )
	{
		uint32_t width = d->width;
		uint32_t height = d->height;
		
		uint32_t screenWidth = draw::Draw::get().getScreenWidth();
		uint32_t screenHeight = draw::Draw::get().getScreenHeight();

		bool left = p->x + width < 0;
		bool right = p->x > screenWidth;
		bool top = p->y + height < 0;
		bool bottom = p->y > screenHeight;

		if ( left || right || top || bottom )
		{
			CHECK( entity->onWindowExit( left, right, top, bottom ) );
		}

		return true;
	}

	uint32_t WindowExitCollision::getType()
	{
		return typeId;
	}
} // component