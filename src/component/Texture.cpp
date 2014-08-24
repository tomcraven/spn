#include "component/Texture.h"
#include "component/Dimensions.h"
#include "draw/TexturePool.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	Texture::Texture() : texture( 0 )
	{
	}

	void Texture::setTexture( const char* path, Dimensions& d )
	{
		texture = draw::TexturePool::get().loadTexture( path );
		d.width = getWidth();
		d.height = getHeight();
	}

	CIw2DImage* Texture::getTexture()
	{
		return texture;
	}

	uint32_t Texture::getWidth()
	{
		return static_cast<uint32_t>( texture->GetWidth() );
	}

	uint32_t Texture::getHeight()
	{
		return static_cast<uint32_t>( texture->GetHeight() );
	}

	uint32_t Texture::getType()
	{
		return typeId;
	}

	bool Texture::needsUpdating()
	{
		return false;
	}
}