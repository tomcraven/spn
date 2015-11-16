#ifndef DRAW_DRAW_H
#define DRAW_DRAW_H

#include "core/Types.h"
#include "math/Rect.h"

class CIw2DImage;
class CIw2DSurface;
class CIw2DFont;

namespace component
{
	class Texture;
	class Position;
}

namespace draw
{
	class Draw
	{
	public:
		Draw();

		static Draw& get();
		bool shutdown();
		bool init();
		bool initFont();

		void setViewportCentre( const component::Position* position );

		void setColour( uint32_t colour );
		uint32_t getColour();

		uint32_t getTextWidth( const char* text );
		uint32_t getTextHeight();
		
		void blit( component::Texture* texture, float x, float y, float scale, float r );
		void blitRegion( component::Texture* texture, 
			math::Rect< uint32_t > sourceRect, 
			float x, float y, float scale = 1.0f, float r = 0.0f );
		void text( const char* text, float x, float y, float width = 0.0f, float height = 0.0f );
		void filledRect( float x, float y, float width, float height );
		void filledCircle( float x, float y, float radius );

		static uint32_t getScreenWidth();
		static uint32_t getScreenHeight();

		bool flip();
		bool clear( uint32_t colour );

		float inverseScaleValue( float val );
		float scaleValue( float val );
		void setScale( float scale );
		bool rescale( float scale );
		
		///@todo wtf is the difference between these two functions?
		void convertScreenToWorldCoorinatesA( uint32_t x, uint32_t y, float& outX, float& outY );
		void convertScreenToWorldCoorinatesB( uint32_t x, uint32_t y, float& outX, float& outY );

	private:
		bool initialiseSurface();
		bool shutdownSurface();

		CIw2DSurface* surface;
		CIw2DImage* surfaceImage;
		CIw2DFont* font;

		float scale;
		float inverseScale;
		
		float viewport[2];
	};
}

#endif