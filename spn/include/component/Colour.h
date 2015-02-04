#ifndef COMPONENT_COLOUR_H
#define COMPONENT_COLOUR_H

#include "component/IComponent.h"

namespace component
{
	class Colour : public IComponent
	{
	public:
		Colour();
		Colour( uint32_t alpha, uint32_t red, uint32_t green, uint32_t blue );
		const uint32_t serialise();

		uint32_t alpha, red, green, blue;

	public: // Component
		virtual uint32_t getType();
	};
}

#endif