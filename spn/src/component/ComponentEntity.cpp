#include "component/ComponentEntity.h"
#include "component/IComponent.h"

#include "core/Assert.h"

namespace component
{
	bool ComponentEntity::attach( IComponent* component )
	{
		components.push_back( component );
		return true;
	}

	bool ComponentEntity::init()
	{
		std::vector< component::IComponent* >::iterator compIter = components.begin();
		for ( ; compIter != components.end(); ++compIter )
		{
			VALIDATE( (*compIter)->init( this ) );
		}
		return true;
	}

	bool ComponentEntity::shutdown()
	{
		std::vector< component::IComponent* >::iterator compIter = components.begin();
		for ( ; compIter != components.end(); ++compIter )
		{
			VALIDATE( (*compIter)->shutdown( this ) );
		}
		return true;
	}

	bool ComponentEntity::update( float timeStep )
	{
		std::vector< component::IComponent* >::iterator compIter = components.begin();
		for ( ; compIter != components.end(); ++compIter )
		{
			VALIDATE( (*compIter)->update( this, timeStep ) );
		}
		return true;
	}
}