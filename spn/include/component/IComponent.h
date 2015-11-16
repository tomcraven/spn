#ifndef COMPONENT_ICOMPONENT_H
#define COMPONENT_ICOMPONENT_H

#include "core/Types.h"
#include "core/List.h"

namespace component
{
	class ComponentEntity;

	class IComponent : public core::ListNode
	{
	public:
		virtual ~IComponent() {}

		virtual uint32_t getType() = 0;
		static uint32_t generateTypeId();

		virtual bool initComponent( ComponentEntity* entity ) { return true; }
		virtual bool shutdown( ComponentEntity* entity ) { return true; }
		virtual bool update( ComponentEntity* entity, float timeStep ) { return true; }
	};
}

#endif