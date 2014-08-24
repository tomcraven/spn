#ifndef COMPONENT_WINDOWEXITCOLLISION_H
#define COMPONENT_WINDOWEXITCOLLISION_H

#include "component/IComponent.h"

namespace component
{
	class WindowExitCollision : public IComponent
	{
	public: // Component
		virtual bool update( ComponentEntity* entity, float timeStep );
		virtual uint32_t getType();
		virtual bool needsUpdating();
	};
}

#endif