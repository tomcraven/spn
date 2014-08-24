#include "component/Clickable.h"
#include "component/ComponentEntity.h"
#include "component/Position.h"
#include "component/Dimensions.h"
#include "core/Assert.h"
#include "math/Intersect.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	bool Clickable::onAttach( ComponentEntity* entity )
	{
		CHECK( input::Input::get().addConsumer( this ) );
		return true;
	}

	bool Clickable::update( ComponentEntity* entity, float timeStep )
	{
		if ( clickPositions.size() == 0 )
		{
			return true;
		}

		Position* position = entity->getComponent<Position>();
		Dimensions* d = entity->getComponent<Dimensions>();

		std::vector<ClickPosition>::iterator clickPositionIter = clickPositions.begin();
		for ( ; clickPositionIter != clickPositions.end(); ++clickPositionIter )
		{
			ClickPosition& pos = *clickPositionIter;
			if ( math::Intersect::pointRect( pos.x, 
				pos.y, 
				static_cast<uint32_t>( position->x ), 
				static_cast<uint32_t>( position->y ), 
				d->width, 
				d->height ) )
			{
				entity->onClickableConsumerClick();
			}
		}

		std::vector<ClickPosition> temp;
		clickPositions.swap( temp );

		return true;
	}

	uint32_t Clickable::getType()
	{
		return typeId;
	}
	
	bool Clickable::onInputConsumerButtonDown( uint32_t x, uint32_t y )
	{
		clickPositions.push_back( ClickPosition( x, y ) );
		return true;
	}
}