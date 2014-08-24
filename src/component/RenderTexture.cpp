#include "component/RenderTexture.h"
#include "component/Position.h"

#include "draw/TexturePool.h"
#include "draw/Draw.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	void RenderTexture::setTexture( Texture* inTexture )
	{
		texture = inTexture;
	}

	bool RenderTexture::render( const Position& p )
	{
		draw::Draw::get().blit( texture->getTexture(), p.x, p.y );
		return true;
	}

	uint32_t RenderTexture::getType()
	{
		return typeId;
	}
} // component