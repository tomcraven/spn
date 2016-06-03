#include "component/Texture.h"
#include "component/Dimensions.h"
#include "component/ComponentEntity.h"
#include "core/Assert.h"
#include "draw/TexturePool.h"
#include "core/Platform.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	Texture::Texture() : dimensions( 0 )
	{
	}

	void Texture::setTexturePath( const char* path )
	{
		texture = draw::TexturePool::get().loadTexture( path );

		int width, height;
		SDL_QueryTexture( texture, 0, 0, &width, &height );

		dimensions->width = static_cast< uint32_t >( width );
		dimensions->height = static_cast< uint32_t >( height );
		dimensions->halfWidth = static_cast< uint32_t >( width / 2 );
		dimensions->halfHeight = static_cast< uint32_t >( height / 2 );
	}

	SDL_Texture* Texture::getTexture()
	{
		return texture;
	}

	uint32_t Texture::getWidth()
	{
		return dimensions->width;
	}

	uint32_t Texture::getHeight()
	{
		return dimensions->height;
	}

	uint32_t Texture::getType()
	{
		return typeId;
	}

	bool Texture::init( ComponentEntity* entity )
	{
		entity->getComponent< Dimensions >( &dimensions );
		return true;
	}
}
