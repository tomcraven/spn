#include "component/Texture.h"
#include "component/Dimensions.h"
#include "component/ComponentEntity.h"
#include "core/Assert.h"
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

	void Texture::setTexturePath( const char* path )
	{
		texture = draw::TexturePool::get().loadTexture( path );
		dimensions->width = getWidth();
		dimensions->height = getHeight();
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

	bool Texture::init( ComponentEntity* entity )
	{
		CHECK( entity->getComponent<Dimensions>( &dimensions ) );
		return true;
	}
}