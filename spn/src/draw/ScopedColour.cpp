#include "draw/ScopedColour.h"
#include "draw/ColourConstants.h"
#include "draw/Draw.h"

namespace draw
{
	ScopedColour::ScopedColour( uint32_t colour )
	{
		draw::Draw::get().setColour( colour );
	}

	ScopedColour::~ScopedColour()
	{
		draw::Draw::get().setColour( draw::colour::kDefault );
	}
}