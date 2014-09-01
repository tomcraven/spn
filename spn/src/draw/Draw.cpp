#include "draw/Draw.h"
#include "core/Assert.h"

#include <Iw2D.h>
#include <IwGx.h>

namespace
{
	draw::Draw instance;
	float scale = 1.0f;
}

namespace draw
{
	Draw& Draw::get()
	{
		return instance;
	}

	bool Draw::shutdown()
	{
		delete surfaceImage;
		delete surface;
		delete font;
		Iw2DTerminate();
		return true;
	}

	bool Draw::init()
	{
		Iw2DInit();
		
		font = Iw2DCreateFont( "assets/arial8.gxfont" );
		CHECK( font );

		uint32_t width = uint32_t( float( IwGxGetScreenWidth() ) / scale );
		uint32_t height = uint32_t( float( IwGxGetScreenHeight() ) / scale );
		surface = Iw2DCreateSurface( width, height );
		CHECK( surface );

		surfaceImage = Iw2DCreateImage( surface );
		CHECK( surfaceImage );
		
		surfaceImage->GetMaterial()->SetFiltering( false );
		Iw2DSetUseMipMapping( false );

		return true;
	}

	void Draw::blit( CIw2DImage* texture, float x, float y )
	{
		Iw2DDrawImage( texture, 
			CIwFVec2( x, y ), 
			CIwFVec2( texture->GetWidth(), texture->GetHeight() ) );
	}

	void Draw::text( const char* text, float x, float y )
	{
		Iw2DDrawString( text, 
			CIwFVec2( x, y ),
			CIwFVec2( static_cast< float >( Iw2DGetStringWidth( text ) ), 10.0f ),
			IW_2D_FONT_ALIGN_CENTRE,
			IW_2D_FONT_ALIGN_CENTRE );
	}

	uint32_t Draw::getScreenWidth()
	{
		return Iw2DGetSurfaceWidth();
	}

	uint32_t Draw::getScreenHeight()
	{
		return Iw2DGetSurfaceHeight();
	}

	bool Draw::flip()
	{
		CHECK( Iw2DSetSurface( 0 ) );
		Iw2DDrawImage( surfaceImage, 
			CIwFVec2( 0, 0 ), 
			CIwFVec2( scaleValue( surfaceImage->GetWidth() ), scaleValue( surfaceImage->GetHeight() ) ) );
		Iw2DSurfaceShow();
		CHECK( Iw2DSetSurface( surface ) );

		return true;
	}

	bool Draw::clear( uint32_t colour )
	{
		Iw2DSurfaceClear( colour );
		return true;
	}

	float Draw::scaleValue( float val )
	{
		return val * scale;
	}

	void Draw::setScale( float inScale )
	{
		scale = inScale;
	}
}