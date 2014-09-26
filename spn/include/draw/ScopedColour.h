#ifndef DRAW_SCOPEDCOLOUR_H
#define DRAW_SCOPEDCOLOUR_H

#include "core/Types.h"

namespace draw
{
	class ScopedColour
	{
	public:
		explicit ScopedColour( uint32_t colour );
		~ScopedColour();
	};
}

#endif // DRAW_SCOPEDCOLOUR_H