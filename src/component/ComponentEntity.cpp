#include "component/ComponentEntity.h"
#include "component/IComponent.h"

#include "core/Assert.h"

namespace component
{
	ComponentEntity::ComponentEntity() : numComponents( 0 ), numUpdatableComponents( 0 )
	{
	}

	bool ComponentEntity::attach( IComponent* component )
	{
		CHECK( numComponents != kMaxComponents );
		components[numComponents] = component;
		++numComponents;

		if ( component->needsUpdating() )
		{
			CHECK( numUpdatableComponents != kMaxUpdatableComponents );
			updatableComponents[numUpdatableComponents] = component;
			++numUpdatableComponents;
		}

		component->onAttach( this );

		return true;
	}

	bool ComponentEntity::update( float timeStep )
	{
		for ( uint32_t i = 0; i < numUpdatableComponents; ++i )
		{
			CHECK( updatableComponents[i]->update( this, timeStep ) );
		}

		return true;
	}
}