#include "draw/Draw.h"
#include "core/Assert.h"

#include <Iw2D.h>
#include <IwGx.h>

namespace
{
	draw::Draw instance;

	float kScale = 2.0f;
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
		Iw2DTerminate();
		return true;
	}

	bool Draw::init()
	{
		Iw2DInit();
		
		uint32_t width = uint32_t( float( IwGxGetScreenWidth() ) / kScale );
		uint32_t height = uint32_t( float( IwGxGetScreenHeight() ) / kScale );
		surface = Iw2DCreateSurface( width, height );
		surfaceImage = Iw2DCreateImage( surface );
		
		surfaceImage->GetMaterial()->SetFiltering( false );

		return true;
	}

	void Draw::blit( CIw2DImage* texture, float x, float y )
	{
		Iw2DDrawImage( texture, 
			CIwFVec2( x, y ), 
			CIwFVec2( texture->GetWidth(), texture->GetHeight() ) );
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
#if 0
		Iw2DFinishDrawing();
#endif
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
		return val * kScale;
	}
}