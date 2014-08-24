#include "component/RenderSheet.h"
#include "component/Position.h"
#include "component/Dimensions.h"
#include "component/Texture.h"
#include "component/ComponentEntity.h"

#include "core/Assert.h"

#include "draw/TexturePool.h"
#include "draw/Draw.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	RenderSheet::RenderSheet() : frameWidth( 0 ), frameHeight( 0 ), numFramesX( 0 ), numFramesY( 0 ), speed( 0 )
	{
		currentFrame[0] = 0;
		currentFrame[1] = 0;
	}

	void RenderSheet::setTexture( Texture* t, Dimensions* d, uint32_t inFrameWidth, uint32_t inFrameHeight, float inSpeed )
	{
		r.setTexture( t );
		texture = t;

		frameWidth = inFrameWidth;
		frameHeight = inFrameHeight;
		numFramesX = t->getWidth() / inFrameWidth;
		numFramesY = t->getHeight() / inFrameHeight;
		speed = inSpeed;
		timeUntilFrameChange = inSpeed;

		d->width = frameWidth;
		d->height = frameHeight;
	}

	bool RenderSheet::render( const Position& p )
	{
		CIw2DImage* image = texture->getTexture();
		Iw2DDrawImageRegion( image,
			CIwFVec2( p.x, p.y ),
			CIwFVec2( static_cast<float>( currentFrame[0] * frameWidth ), 
				static_cast<float>( currentFrame[1] * frameHeight ) ),
			CIwFVec2( static_cast<float>( frameWidth ), static_cast<float>( frameHeight ) ) );

		return true;
	}

	bool RenderSheet::update( ComponentEntity* entity, float timeStep )
	{
		CHECK( updateCurrentFrame( timeStep, entity ) );
		return true;
	}

	uint32_t RenderSheet::getType()
	{
		return typeId;
	}

	bool RenderSheet::needsUpdating()
	{
		return true;
	}

	bool RenderSheet::updateCurrentFrame( float timeStep, ComponentEntity* entity )
	{
		timeUntilFrameChange -= timeStep;

		if ( shouldIncrementFrame( entity ) )
		{
			incrementFrame();
			timeUntilFrameChange = speed;
		}

		return true;
	}

	bool RenderSheet::shouldIncrementFrame( ComponentEntity* entity )
	{
		return timeUntilFrameChange <= 0;
	}

	void RenderSheet::incrementFrame()
	{
		currentFrame[0] += 1;
		if ( currentFrame[0] >= numFramesX )
		{
			currentFrame[0] = 0;
			currentFrame[1] += 1;
			if ( currentFrame[1] >= numFramesY )
			{
				currentFrame[1] = 0;
			}
		}
	}

} // component