#ifndef DRAW_DRAW_H
#define DRAW_DRAW_H

#include "core/Types.h"

class CIw2DImage;
class CIw2DSurface;
class CIw2DFont;

namespace draw
{
	class Draw
	{
	public:
		static Draw& get();
		bool shutdown();
		bool init();

		void setColour( uint32_t colour );
		uint32_t getColour();

		void blit( CIw2DImage* texture, float x, float y );
		void text( const char* text, float x, float y );
		void filledRect( float x, float y, float width, float height );
		void filledCircle( float x, float y, float radius );

		uint32_t getScreenWidth();
		uint32_t getScreenHeight();

		bool flip();
		bool clear( uint32_t colour );

		float inverseScaleValue( float val );
		float scaleValue( float val );
		void setScale( float scale );

	private:
		CIw2DSurface* surface;
		CIw2DImage* surfaceImage;
		CIw2DFont* font;

		float scale;
	};
}

#endif