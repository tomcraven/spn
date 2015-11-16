#ifndef COMPONENT_INTERACTBASE_H
#define COMPONENT_INTERACTBASE_H

#include "component/IComponent.h"

namespace component
{
	class InteractBase : public IComponent
	{
	public:
		virtual bool go();

	public: // Component
		virtual uint32_t getType();
	};
}

#endif