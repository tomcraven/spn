#include "component/Clickable.h"
#include "component/ComponentEntity.h"
#include "component/Position.h"
#include "component/Dimensions.h"
#include "core/Assert.h"
#include "draw/Draw.h"
#include "math/Intersect.h"

#include <stdio.h>

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();

	class NullConsumer : public component::Clickable::Consumer
	{
	public:
		bool onClickableConsumerClick()
		{
			return true;
		}
	};
}

namespace component
{
	Clickable::Clickable()
	{
		setConsumer( 0 );
	}

	bool Clickable::initComponent( ComponentEntity* entity )
	{
		VALIDATE( entity->getComponent<Position>( &position ) );
		VALIDATE( entity->getComponent<Dimensions>( &dimensions ) );
		
		VALIDATE( input::Input::get().addConsumer( this ) );

		hasClickPosition = false;

		return true;
	}

	bool Clickable::shutdown( ComponentEntity* entity )
	{
		VALIDATE( input::Input::get().removeConsumer( this ) );
		return true;
	}

	bool Clickable::update( ComponentEntity* entity, float timeStep )
	{
		//if ( !hasClickPosition )
		//{
		//	return true;
		//}

		//float clickRadius = 8.0f;
		//if ( math::intersect::circleRect( 
		//	static_cast< float >( clickPositionX ),
		//	static_cast< float >( clickPositionY ),
		//	clickRadius,
		//	position->x, 
		//	position->y, 
		//	static_cast< float >( dimensions->width ),
		//	static_cast< float >( dimensions->height ) ) )
		//{
		//	VALIDATE( consumer->onClickableConsumerClick() );
		//}

		//hasClickPosition = false;

		return true;
	}

	uint32_t Clickable::getType()
	{
		return typeId;
	}

	void Clickable::setConsumer( Consumer* inConsumer )
	{
		if ( inConsumer )
		{
			consumer = inConsumer;
		}
		else
		{
			static NullConsumer nullConsumer;
			consumer = &nullConsumer;
		}
	}
	
	bool Clickable::onInputConsumerButtonDown( uint32_t x, uint32_t y )
	{
		hasClickPosition = true;
		draw::Draw::get().convertScreenToWorldCoorinatesA( x, y, clickPositionX, clickPositionY );

		float clickRadius = 4.0f;
		if ( math::intersect::circleRect( 
			clickPositionX,
			clickPositionY,
			clickRadius,
			position->x, 
			position->y, 
			static_cast< float >( dimensions->width ),
			static_cast< float >( dimensions->height ) ) )
		{
			VALIDATE( consumer->onClickableConsumerClick() );
		}

		return true;
	}
}