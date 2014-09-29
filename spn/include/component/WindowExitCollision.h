#ifndef COMPONENT_WINDOWEXITCOLLISION_H
#define COMPONENT_WINDOWEXITCOLLISION_H

#include "component/IComponent.h"

namespace component
{
	class Position;
	class Dimensions;

	class WindowExitCollision : public IComponent
	{
	public: // Component
		virtual bool init( ComponentEntity* entity );
		virtual bool update( ComponentEntity* entity, float timeStep );
		virtual uint32_t getType();

	private:
		Position* p;
		Dimensions* d;
	};
}

#endif