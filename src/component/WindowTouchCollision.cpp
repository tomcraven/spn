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
	bool WindowTouchCollision::update( ComponentEntity* entity, float timeStep )
	{
		Position* p = entity->getComponent<Position>();
		Dimensions* d = entity->getComponent<Dimensions>();

		uint32_t width = d->width;
		uint32_t height = d->height;

		bool left = p->x < 0;
		bool right = p->x + width > draw::Draw::get().getScreenWidth();
		bool top = p->y < 0;
		bool bottom = p->y + height > draw::Draw::get().getScreenHeight();

		CHECK( entity->onWindowTouch( left, right, top, bottom ) );

		return true;
	}

	uint32_t WindowTouchCollision::getType()
	{
		return typeId;
	}

	bool WindowTouchCollision::needsUpdating()
	{
		return true;
	}
} // component