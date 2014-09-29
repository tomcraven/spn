#ifndef COMPONENT_WINDOWTOUCHCOLLISION_H
#define COMPONENT_WINDOWTOUCHCOLLISION_H

#include "component/IComponent.h"

namespace component
{
	class Position;
	class Dimensions;

	class WindowTouchCollision : public IComponent
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