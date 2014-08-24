#ifndef COMPONENT_ICOMPONENT_H
#define COMPONENT_ICOMPONENT_H

#include "core/Types.h"

namespace component
{
	class ComponentEntity;

	class IComponent
	{
	public:
		IComponent() : flagNeedsUpdating( false ) {}
		virtual ~IComponent() {}

		virtual uint32_t getType() = 0;
		static uint32_t generateTypeId();

		virtual bool init( ComponentEntity* entity ) { return true; }
		virtual bool needsUpdating() { return flagNeedsUpdating; }
		virtual bool update( ComponentEntity* entity, float timeStep ) { return true; }
		virtual bool onAttach( ComponentEntity* entity ) { return true; }

	protected:
		bool flagNeedsUpdating;
	};
}

#endif