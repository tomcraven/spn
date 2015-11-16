#include "draw/Draw.h"
#include "draw/ColourConstants.h"
#include "core/Assert.h"
#include "component/Texture.h"
#include "component/Position.h"
#include "math/math.h"
#include "core/Algorithm.h"

#include <sdl.h>
#include <sdl_image.h>
#include <sdl_ttf.h>

// remove
#include <stdio.h>

namespace
{
	const uint32_t kScreenWidth = 640;
	const uint32_t kScreenHeight = 480;
}

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

		TTF_CloseFont( font );
		TTF_Quit();

		return true;
	}

	bool Draw::init()
	{
		SDL_CreateWindowAndRenderer( kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN, &window, &windowRenderer );
		viewport[0] = kScreenWidth / 2;
		viewport[1] = kScreenHeight / 2;

		SDL_SetRenderDrawBlendMode( windowRenderer, SDL_BLENDMODE_BLEND );

		VALIDATE( ( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) == IMG_INIT_PNG );

		VALIDATE( initFont() );

		return true;
	}

	bool Draw::initFont()
	{
		VALIDATE( TTF_Init() == 0 );
		
		font = TTF_OpenFont( "font/font.ttf", 14 );
		VALIDATE( font );
		
		TTF_SizeText( font, "", 0, &textHeight );

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
		int width = 0;
		TTF_SizeText( font, text, &width, 0 );
		return width;
	}

	uint32_t Draw::getTextHeight()
	{
		return textHeight;
	}

	void Draw::blit( component::Texture* textureComponent, float x, float y, float scale, float r )
	{
		SDL_Texture* texture = textureComponent->getTexture();
		float width = static_cast< float >( textureComponent->getWidth() );
		float height = static_cast< float >( textureComponent->getHeight() );
		
		blitInternal( texture, x, y, scale, r, width, height );
	}

	void Draw::blitInternal( SDL_Texture* texture, float x, float y, float scale, float r, float inWidth, float inHeight )
	{
		if ( colour != 0 )
		{
			uint8_t r, g, b, a;
			draw::colour::rgbaFromColour( colour, r, g, b, a );
			SDL_SetTextureColorMod( texture, r, g, b );
			SDL_SetTextureAlphaMod( texture, a );
			colour = 0;
		}
		
		if ( ( inWidth == 0 ) || ( inHeight == 0 ) )
		{
			int tempW, tempH;
			SDL_QueryTexture( texture, 0, 0, &tempW, &tempH );

			inWidth = static_cast< float >( tempW );
			inHeight = static_cast< float >( tempH );
		}

		float width = inWidth;
		float height = inHeight;

		float oneMinusScaleWidth = width * ( 1.0f - scale );
		float oneMinusScaleHeight = height * ( 1.0f - scale );

		float scaledCentreWidth = ( oneMinusScaleWidth / 2 );
		float scaledCentreHeight = ( oneMinusScaleHeight / 2 );
		
		SDL_Rect destRect;
		float destRectX = ( ( x + scaledCentreWidth ) / scale );
		float destRectY = ( ( y + scaledCentreHeight ) / scale );
		destRect.w = core::algorithm::round( inWidth );
		destRect.h = core::algorithm::round( inHeight );
		
		destRectX += ( inverseScaleValue( kScreenWidth ) / 2.0f ) - viewport[0];
		destRectY += ( inverseScaleValue( kScreenHeight ) / 2.0f ) - viewport[1];

		destRect.x = core::algorithm::round( destRectX );
		destRect.y = core::algorithm::round( destRectY );
	
		SDL_Point centrePoint;
		centrePoint.x = core::algorithm::round( width / 2.0f );
		centrePoint.y = core::algorithm::round( height / 2.0f );
		
		SDL_RenderSetScale( windowRenderer, scale * this->scale, scale * this->scale );
		float rotationDegrees = r * ( 180.0f / math::pi );
		SDL_RenderCopyEx( windowRenderer, texture, 0, &destRect, rotationDegrees, &centrePoint, SDL_FLIP_NONE );
	}

	void Draw::blitRegion( component::Texture* textureComponent, 
			math::Rect< uint32_t > sourceRect, 
			float x, float y, float scale, float r )
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
		
		SDL_Rect destRect;
		destRect.x = static_cast< int >( x + ( ( getScreenWidth() / 2 ) - viewport[0] ) );
		destRect.y = static_cast< int >( y + ( ( getScreenHeight() / 2 ) - viewport[1] ) );
		destRect.w = sourceRect.w;
		destRect.h = sourceRect.h;

		SDL_Point centrePoint;
		centrePoint.x = ( sourceRect.w / 2 );
		centrePoint.y = ( sourceRect.h / 2 );
		
		SDL_RenderSetScale( windowRenderer, scale * this->scale, scale * this->scale );
		float rotationDegrees = r * ( 180.0f / math::pi );

		SDL_Rect sourceSDLRect;
		sourceSDLRect.x = sourceRect.x;
		sourceSDLRect.y = sourceRect.y;
		sourceSDLRect.w = sourceRect.w;
		sourceSDLRect.h = sourceRect.h;

		SDL_RenderCopyEx( windowRenderer, texture, &sourceSDLRect, &destRect, rotationDegrees, &centrePoint, SDL_FLIP_NONE );
	}

	void Draw::text( const char* text, float x, float y, float width, float height )
	{
		SDL_Color sdlColour;
		draw::colour::rgbaFromColour( colour, sdlColour.r, sdlColour.g, sdlColour.b, sdlColour.a );

		SDL_Surface* surface = TTF_RenderText_Solid( font, text, sdlColour );
		SDL_Texture* texture = createTextureFromSurface( surface );

		blitInternal( texture, x, y, 1.0f, 0.0f, width, height );

		SDL_DestroyTexture( texture );
		SDL_FreeSurface( surface );
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
		return core::algorithm::round( get().inverseScaleValue( kScreenWidth ) );
	}

	uint32_t Draw::getScreenHeight()
	{
		return core::algorithm::round( get().inverseScaleValue( kScreenHeight ) );
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

	void Draw::setViewportCentre( component::Position* position )
	{
		viewport[0] = position->x;
		viewport[1] = position->y;
	}

	void Draw::convertScreenToWorldCoorinatesA( uint32_t x, uint32_t y, float& outX, float& outY )
	{
		int32_t screenDiff[2] = 
		{
			( kScreenWidth / 2 ) - x,
			( kScreenHeight / 2 ) - y
		};

		outX = viewport[0] - inverseScaleValue( screenDiff[0] );
		outY = viewport[1] - inverseScaleValue( screenDiff[1] );
	}

	void Draw::convertScreenToWorldCoorinatesB( uint32_t x, uint32_t y, float& outX, float& outY )
	{
		int32_t screenDiff[2] = 
		{
			static_cast< int32_t >( ( inverseScaleValue( kScreenWidth ) / 2 ) - x ),
			static_cast< int32_t >( ( inverseScaleValue( kScreenHeight ) / 2 ) - y )
		};

		outX = viewport[0] - screenDiff[0];
		outY = viewport[1] - screenDiff[1];
	}
}