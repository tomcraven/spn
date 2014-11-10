#include "component/WindowExitCollision.h"
#include "component/ComponentEntity.h"
#include "component/Position.h"
#include "component/Dimensions.h"
#include "core/Assert.h"
#include "draw/Draw.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();

	class NullWindowExitCollisionListener : public component::WindowExitCollision::IWindowExitCollisionListener
	{
		virtual bool onWindowExit( component::ComponentEntity* entity, bool left, bool right, bool top, bool bottom )
		{
			return true;
		}
	};
}

namespace component
{
	bool WindowExitCollision::setConsumer( IWindowExitCollisionListener* inConsumer )
	{
		if ( inConsumer )
		{
			consumer = inConsumer;
		}
		else
		{
			static NullWindowExitCollisionListener nullWindowExitCollisionListener;
			consumer = &nullWindowExitCollisionListener;
		}
		return true;
	}

	bool WindowExitCollision::init( ComponentEntity* inEntity )
	{
		entity = inEntity;
		VALIDATE( entity->getComponent< Position >( &p ) );
		VALIDATE( entity->getComponent< Dimensions >( &d ) );
		VALIDATE( setConsumer( dynamic_cast< IWindowExitCollisionListener* >( entity ) ) );

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
			VALIDATE( consumer->onWindowExit( entity, left, right, top, bottom ) );
		}

		return true;
	}

	uint32_t WindowExitCollision::getType()
	{
		return typeId;
	}
} // component