#ifndef COMPONENT_DIMENSIONS_H
#define COMPONENT_DIMENSIONS_H

#include "core/Types.h"
#include "component/IComponent.h"

namespace component
{
	class Dimensions : public IComponent
	{
	public:
		uint32_t width, height;

	public: // Component
		virtual uint32_t getType();
		virtual bool needsUpdating();
	};
}

#endif