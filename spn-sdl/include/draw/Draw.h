#ifndef DRAW_DRAW_H
#define DRAW_DRAW_H

#include "core/Types.h"
#include "math/Rect.h"

namespace component
{
	class Texture;
	class Position;
}

struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;
struct SDL_Texture;
struct _TTF_Font;

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

		template< class T >
		float inverseScaleValue( const T& val )
		{
			return inverseScale * static_cast< float >( val );
		}

		template< class T >
		float scaleValue( const T& val )
		{
			return scale * static_cast< float >( val );
		}

		void setScale( float scale );
		bool rescale( float scale );

		SDL_Texture* createTextureFromSurface( SDL_Surface* image );

		void setViewportCentre( component::Position* position );

		///@todo wtf is the difference between these two functions?
		void convertScreenToWorldCoorinatesA( uint32_t x, uint32_t y, float& outX, float& outY );
		void convertScreenToWorldCoorinatesB( uint32_t x, uint32_t y, float& outX, float& outY );

	private:
		void blitInternal( SDL_Texture* texture, float x, float y, float scale, float r, float inWidth = 0, float inHeight = 0 );

	public:
		float scale;
		float inverseScale;

		SDL_Window* window;
		SDL_Renderer* windowRenderer;
		_TTF_Font* font;
		int textHeight;

		uint32_t colour;

		float viewport[2];
	};
}

#endif