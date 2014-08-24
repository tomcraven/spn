#ifndef COMPONENT_COMPONENTENTITY_H
#define COMPONENT_COMPONENTENTITY_H

#include "core/Types.h"
#include "game/Entity.h"
#include "component/IComponent.h"

namespace component
{
	class ComponentEntity : public game::Entity
	{
	public:
		ComponentEntity();
		bool attach( component::IComponent* component );

		template<class T>
		T* getComponent()
		{
			uint32_t type = T().getType();
			for ( uint32_t i = 0; i < numComponents; ++i )
			{
				if ( type == components[i]->getType() )
				{
					return reinterpret_cast<T*>( components[i] );
				}
			}

			return 0;
		}

		bool update( float timeStep );

	private:
		// @todo do something about this...
		static const uint32_t kMaxComponents = 16;
		component::IComponent* components[kMaxComponents];
		uint32_t numComponents;

		static const uint32_t kMaxUpdatableComponents = 4;
		component::IComponent* updatableComponents[kMaxUpdatableComponents];
		uint32_t numUpdatableComponents;
	};
}

#endif