#include "component/Clickable.h"
#include "component/ComponentEntity.h"
#include "component/Position.h"
#include "component/Dimensions.h"
#include "core/Assert.h"
#include "draw/Draw.h"
#include "math/Intersect.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	bool Clickable::init( ComponentEntity* entity )
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
		if ( !hasClickPosition )
		{
			return true;
		}

		if ( math::Intersect::pointRect( 
			clickPositionX, clickPositionY,
			static_cast<uint32_t>( position->x ), 
			static_cast<uint32_t>( position->y ), 
			dimensions->width, 
			dimensions->height ) )
		{
			VALIDATE( entity->onClickableConsumerClick() );
		}

		hasClickPosition = false;

		return true;
	}

	uint32_t Clickable::getType()
	{
		return typeId;
	}
	
	bool Clickable::onInputConsumerButtonDown( uint32_t x, uint32_t y )
	{
		hasClickPosition = true;
		clickPositionX = static_cast< uint32_t >(
			draw::Draw::get().inverseScaleValue( static_cast< float >( x ) ) );
		clickPositionY = static_cast< uint32_t >(
			draw::Draw::get().inverseScaleValue( static_cast< float >( y ) ) );
		return true;
	}
}