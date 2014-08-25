#ifndef COMPONENT_VELOCITY_H
#define COMPONENT_VELOCITY_H

#include "component/IComponent.h"
#include "core/Types.h"

namespace component
{
	class Position;

	class Velocity : public IComponent
	{
	public: // IComponent
		virtual bool init( ComponentEntity* entity );
		virtual bool update( ComponentEntity* entity, float timeStep );
		virtual uint32_t getType();

		float x, y;

	private:
		Position* p;
	};
} 

#endif