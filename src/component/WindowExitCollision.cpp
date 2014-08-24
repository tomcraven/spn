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
	bool WindowExitCollision::update( ComponentEntity* entity, float timeStep )
	{
		Position* p = entity->getComponent<Position>();
		Dimensions* d = entity->getComponent<Dimensions>();

		uint32_t width = d->width;
		uint32_t height = d->height;

		bool left = p->x + width < 0;
		bool right = p->x > draw::Draw::get().getScreenWidth();
		bool top = p->y + height < 0;
		bool bottom = p->y > draw::Draw::get().getScreenHeight();

		CHECK( entity->onWindowExit( left, right, top, bottom ) );

		return true;
	}

	uint32_t WindowExitCollision::getType()
	{
		return typeId;
	}

	bool WindowExitCollision::needsUpdating()
	{
		return true;
	}
} // component