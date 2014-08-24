#ifndef COMPONENT_ICOMPONENT_H
#define COMPONENT_ICOMPONENT_H

#include "core/Types.h"

namespace component
{
	class ComponentEntity;

	class IComponent
	{
	public:
		virtual uint32_t getType() = 0;
		virtual bool needsUpdating() = 0;

		virtual bool update( ComponentEntity* entity, float timeStep ) { return true; }
		virtual bool onAttach( ComponentEntity* entity ) { return true; }

		static uint32_t generateTypeId();
	};
}

#endif