#ifndef COMPONENT_INPUTCONSUMER_H
#define COMPONENT_INPUTCONSUMER_H

#include "component/IComponent.h"
#include "input/Input.h"

namespace component
{
	class InputConsumer : public IComponent
	{
	public: // IComponent
		virtual bool onAttach( ComponentEntity* entity );
		virtual uint32_t getType();
	};
}

#endif