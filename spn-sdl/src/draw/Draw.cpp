#include "draw/Draw.h"
#include "draw/ColourConstants.h"
#include "core/Assert.h"
#include "component/Texture.h"
#include "math/Math.h"
#include "core/Platform.h"

namespace draw
{
	Draw::Draw() : scale( 1.0f ), inverseScale( 1.0f / scale )
	{
	}

	Draw& Draw::get()
	{
		static draw::Draw instance;
		return instance;
	}

	bool Draw::shutdown()
	{
		SDL_DestroyRenderer( windowRenderer );
		SDL_DestroyWindow( window );

		IMG_Quit();

		return true;
	}

	bool Draw::init()
	{
		SDL_CreateWindowAndRenderer( 640, 480, 0, &window, &windowRenderer );

		SDL_SetRenderDrawBlendMode( windowRenderer, SDL_BLENDMODE_BLEND );

		// Initialise PNG loading
		VALIDATE( ( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) == IMG_INIT_PNG );

		return true;
	}

	bool Draw::initFont()
	{
		return true;
	}

	void Draw::setColour( uint32_t inColour )
	{
		colour = inColour;
	}

	uint32_t Draw::getColour()
	{
		return colour;
	}

	uint32_t Draw::getTextWidth( const char* text )
	{
		return 0;
	}

	uint32_t Draw::getTextHeight()
	{
		return 0;
	}

	void Draw::blit( component::Texture* textureComponent, float x, float y, float scale, float r )
	{
		SDL_Texture* texture = textureComponent->getTexture();

		if ( colour != 0 )
		{
			uint8_t r, g, b, a;
			draw::colour::rgbaFromColour( colour, r, g, b, a );
			SDL_SetTextureColorMod( texture, r, g, b );
			SDL_SetTextureAlphaMod( texture, a );
			colour = 0;
		}

		uint32_t width = textureComponent->getWidth();
		uint32_t height = textureComponent->getHeight();

		float oneMinusScaleWidth = width * ( 1.0f - scale );
		float oneMinusScaleHeight = height * ( 1.0f - scale );

		float uhhhhhYeaWidth = ( oneMinusScaleWidth / 2 );
		float uhhhhhYeaHeight = ( oneMinusScaleHeight / 2 );

		SDL_Rect destRect;
		destRect.x = static_cast< int >( ( x + uhhhhhYeaWidth ) / scale );
		destRect.y = static_cast< int >( ( y + uhhhhhYeaHeight ) / scale );
		destRect.w = width;
		destRect.h = height;

		SDL_Point centrePoint;
		centrePoint.x = ( width / 2 );
		centrePoint.y = ( height / 2 );

		SDL_RenderSetScale( windowRenderer, scale * this->scale, scale * this->scale );
		float rotationDegrees = r * ( 180.0f / math::pi );
		SDL_RenderCopyEx( windowRenderer, texture, 0, &destRect, rotationDegrees, &centrePoint, SDL_FLIP_NONE );
	}

	void Draw::text( const char* text, float x, float y )
	{
	}

	void Draw::filledRect( float x, float y, float width, float height )
	{
		{
			uint8_t r, g, b, a;
			draw::colour::rgbaFromColour( colour, r, g, b, a );
			SDL_SetRenderDrawColor( windowRenderer, r, g, b, a );
		}

		SDL_Rect r;
		r.x = static_cast< int >( x );
		r.y = static_cast< int >( y );
		r.w = static_cast< int >( width );
		r.h = static_cast< int >( height );

		SDL_RenderFillRect( windowRenderer, &r );
	}

	void Draw::filledCircle( float x, float y, float radius )
	{
	}

	uint32_t Draw::getScreenWidth()
	{
		return static_cast< uint32_t >( get().inverseScaleValue( 640 ) );
	}

	uint32_t Draw::getScreenHeight()
	{
		return static_cast< uint32_t >( get().inverseScaleValue( 480 ) );
	}

	bool Draw::flip()
	{
		SDL_RenderPresent( windowRenderer );
		return true;
	}

	bool Draw::clear( uint32_t colour )
	{
		uint8_t r, g, b, a;
		draw::colour::rgbaFromColour( colour, r, g, b, a );

		int ret = SDL_SetRenderDrawColor( windowRenderer, r, g, b, a );
		SDL_RenderClear( windowRenderer );
		return true;
	}

	float Draw::inverseScaleValue( float val )
	{
		return inverseScale * val;
	}

	float Draw::scaleValue( float val )
	{
		return val * scale;
	}

	void Draw::setScale( float inScale )
	{
		scale = inScale;
		inverseScale = 1.0f / scale;
	}

	bool Draw::rescale( float inScale )
	{
		setScale( inScale );
		VALIDATE( clear( colour::kDefault ) );

		return true;
	}

	SDL_Texture* Draw::createTextureFromSurface( SDL_Surface* image )
	{
		return SDL_CreateTextureFromSurface( windowRenderer, image );
	}
}
