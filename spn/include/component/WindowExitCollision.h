#ifndef COMPONENT_WINDOWEXITCOLLISION_H
#define COMPONENT_WINDOWEXITCOLLISION_H

#include "component/IComponent.h"

namespace component
{
	class Position;
	class Dimensions;

	class WindowExitCollision : public IComponent
	{
	public:
		class IWindowExitCollisionListener
		{
		public:
			virtual bool onWindowExit( ComponentEntity* entity, bool left, bool right, bool top, bool bottom ) = 0;
		};
		bool setConsumer( IWindowExitCollisionListener* consumer );

	public: // Component
		virtual bool initComponent( ComponentEntity* entity );
		virtual bool update( ComponentEntity* entity, float timeStep );
		virtual uint32_t getType();

	private:
		Position* p;
		Dimensions* d;
		IWindowExitCollisionListener* consumer;
		ComponentEntity* entity;
	};
}

#endif