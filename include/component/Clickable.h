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
	public: // IComponent
		virtual bool init( ComponentEntity* entity );
		virtual bool onAttach( ComponentEntity* entity );
		virtual uint32_t getType();
		virtual bool update( ComponentEntity* entity, float timeStep );

		class Consumer
		{
		public:
			virtual bool onClickableConsumerClick() = 0;
		};

	public: // input::Input::Consumer
		virtual bool onInputConsumerButtonDown( uint32_t x, uint32_t y );

	private:
		struct ClickPosition
		{
			ClickPosition( uint32_t inX, uint32_t inY ) : x( inX ), y( inY ) {}
			uint32_t x, y;
		};
		std::vector<ClickPosition> clickPositions;

		Position* position;
		Dimensions* dimensions;
	};
}

#endif