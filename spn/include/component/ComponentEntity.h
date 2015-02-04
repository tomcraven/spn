#ifndef COMPONENT_COMPONENTENTITY_H
#define COMPONENT_COMPONENTENTITY_H

#include "core/Types.h"
#include "game/Entity.h"
#include "component/IComponent.h"
#include "core/List.h"

#define USE_COMPONENT( componentEntity, ComponentType, function ) \
	{ \
		ComponentType* component; \
		VALIDATE( ( componentEntity ).getComponent< ComponentType >( &component ) ); \
		component->function; \
	}

#define USE_COMPONENT_PTR( componentEntity, ComponentType, function ) \
	{ \
		ComponentType* component; \
		VALIDATE( ( componentEntity )->getComponent< ComponentType >( &component ) ); \
		component->function; \
	}

namespace component
{
	class ComponentEntity : public game::Entity
	{
	public:
		bool attach( component::IComponent* component );

		template<class T>
		T* getComponent( T** outComponent = 0 )
		{
			uint32_t type = T().getType();
			ComponentContainer::Iterator compIter = components.begin();
			for ( ; compIter != components.end(); ++compIter )
			{
				IComponent* component = *compIter;
				if ( type == component->getType() )
				{
					if ( outComponent )
					{
						*outComponent = static_cast<T*>( component ) ;
						return *outComponent;
					}
					else
					{
						return static_cast<T*>( component );
					}
				}
			}

			return 0;
		}

	public: // game::Entity
		virtual bool init();
		virtual bool shutdown();
		virtual bool update( float timeStep );

	private:
		typedef core::List< component::IComponent* > ComponentContainer;
		ComponentContainer components;
	};
}

#endif