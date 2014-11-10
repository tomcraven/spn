#include "draw/Draw.h"
#include "draw/Colour.h"
#include "core/Assert.h"

#include <Iw2D.h>
#include <IwGx.h>
#include <IwGeomFMat2D.h>

namespace draw
{
	Draw::Draw() : scale( 1.0f ), inverseScale( 1.0f / scale ), font( 0 )
	{
	}

	Draw& Draw::get()
	{
		static draw::Draw instance;
		return instance;
	}

	bool Draw::shutdown()
	{
		VALIDATE( shutdownSurface() );

		if ( font )
		{
			delete font;
			font = 0;
		}

		Iw2DTerminate();
		return true;
	}

	bool Draw::shutdownSurface()
	{
		delete surfaceImage;
		delete surface;
		return true;
	}

	bool Draw::init()
	{
		Iw2DInit();
		VALIDATE( initialiseSurface() );

		return true;
	}

	bool Draw::initFont()
	{
		font = Iw2DCreateFont( "fonts/arial8.gxfont" );
		VALIDATE( font );

		return true;
	}

	bool Draw::initialiseSurface()
	{
		uint32_t width = uint32_t( float( IwGxGetScreenWidth() ) / scale );
		uint32_t height = uint32_t( float( IwGxGetScreenHeight() ) / scale );
		surface = Iw2DCreateSurface( width, height );
		VALIDATE( surface );

		surfaceImage = Iw2DCreateImage( surface );
		VALIDATE( surfaceImage );
		
		surfaceImage->GetMaterial()->SetFiltering( false );
		Iw2DSetUseMipMapping( false );
		
		return true;
	}

	void Draw::setColour( uint32_t colour )
	{
		Iw2DSetColour( colour );
	}

	uint32_t Draw::getColour()
	{
		return Iw2DGetColour().Get();
	}

	uint32_t Draw::getTextWidth( const char* text )
	{
		return Iw2DGetStringWidth( text );
	}

	uint32_t Draw::getTextHeight()
	{
		return font->GetHeight();
	}

	void Draw::blit( CIw2DImage* texture, float x, float y )
	{
		Iw2DDrawImage( texture, 
			CIwFVec2( x, y ), 
			CIwFVec2( texture->GetWidth(), texture->GetHeight() ) );
	}

	void Draw::blit( CIw2DImage* texture, float x, float y, float r )
	{
		CIwFMat2D rotationMat = CIwFMat2D::g_Identity;
		rotationMat.SetRot( r, CIwFVec2( x + ( texture->GetWidth() / 2 ), y + ( texture->GetHeight() / 2 ) ) );
		Iw2DSetTransformMatrix( rotationMat );

		blit( texture, x, y );
		
		Iw2DSetTransformMatrix( CIwFMat2D::g_Identity );
	}

	void Draw::text( const char* text, float x, float y )
	{
		Iw2DDrawString( text, 
			CIwFVec2( x, y ),
			CIwFVec2( static_cast< float >( Iw2DGetStringWidth( text ) ), 10.0f ),
			IW_2D_FONT_ALIGN_CENTRE,
			IW_2D_FONT_ALIGN_CENTRE );
	}

	void Draw::filledRect( float x, float y, float width, float height )
	{
		Iw2DFillRect(
			CIwFVec2( x, y ), 
			CIwFVec2( width, height ) );
	}

	void Draw::filledCircle( float x, float y, float radius )
	{
		Iw2DFillArc( CIwFVec2( x, y ),
			CIwFVec2( radius, radius ),
			0, PI * 2 );
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
		VALIDATE( Iw2DSetSurface( 0 ) );
		Iw2DDrawImage( surfaceImage, 
			CIwFVec2( 0, 0 ), 
			CIwFVec2( scaleValue( surfaceImage->GetWidth() ), scaleValue( surfaceImage->GetHeight() ) ) );
		Iw2DSurfaceShow();
		VALIDATE( Iw2DSetSurface( surface ) );

		return true;
	}

	bool Draw::clear( uint32_t colour )
	{
		Iw2DSurfaceClear( colour );
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

		VALIDATE( shutdownSurface() );
		VALIDATE( initialiseSurface() );
		
		VALIDATE( clear( colour::kDefault ) );
		VALIDATE( Iw2DSetSurface( surface ) );

		return true;
	}
}