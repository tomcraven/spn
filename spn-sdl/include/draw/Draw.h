#ifndef DRAW_DRAW_H
#define DRAW_DRAW_H

#include "core/Types.h"

namespace component
{
	class Texture;
}

struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;
struct SDL_Texture;

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
		void text( const char* text, float x, float y );
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

		SDL_Texture* createTextureFromSurface( SDL_Surface* image );

	private:
		float scale;
		float inverseScale;

		SDL_Window* window;
		SDL_Renderer* windowRenderer;

		uint32_t colour;
	};
}

#endif