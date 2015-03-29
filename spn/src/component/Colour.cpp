#include "component/Colour.h"
#include "draw/ColourConstants.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	Colour::Colour() : alpha( 0u ), red( 0u ), green( 0u ), blue( 0u )
	{
	}

	Colour::Colour( uint32_t alpha, uint32_t red, uint32_t green, uint32_t blue ) : 
		alpha( alpha ), red( red ), green( green ), blue( blue )
	{
	}

	const uint32_t Colour::serialise()
	{
		return draw::colour::colourFromRGBA( red, green, blue, alpha );
	}

	uint32_t Colour::getType()
	{
		return typeId;
	}
} // component