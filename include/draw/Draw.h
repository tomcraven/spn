#ifndef DRAW_DRAW_H
#define DRAW_DRAW_H

#include "core/Types.h"

class CIw2DImage;
class CIw2DSurface;

namespace draw
{
	class Draw
	{
	public:
		static Draw& get();
		bool shutdown();
		bool init();

		void blit( CIw2DImage* texture, float x, float y );

		uint32_t getScreenWidth();
		uint32_t getScreenHeight();

		bool flip();
		bool clear( uint32_t colour );

		float scaleValue( float val );

	private:
		CIw2DSurface* surface;
		CIw2DImage* surfaceImage;
	};
}

#endif