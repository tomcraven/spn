#ifndef COMPONENT_CLICKABLE_H
#define COMPONENT_CLICKABLE_H

#include "component/IComponent.h"
#include "input/Input.h"

namespace component
{
	class Dimensions;
	class Position;

	class Clickable : public IComponent, public input::Input::Consumer
	{
	public:
		Clickable();

	public: // IComponent
		virtual bool initComponent( ComponentEntity* entity );
		virtual bool shutdown( ComponentEntity* entity );
		virtual uint32_t getType();
		virtual bool update( ComponentEntity* entity, float timeStep );

		class Consumer
		{
		public:
			virtual bool onClickableConsumerClick() = 0;
		};
		void setConsumer( Consumer* consumer );

	public: // input::Input::Consumer
		virtual bool onInputConsumerButtonDown( uint32_t x, uint32_t y );

	private:
		bool hasClickPosition;
		float clickPositionX;
		float clickPositionY;

		Position* position;
		Dimensions* dimensions;

		Consumer* consumer;
	};
}

#endif