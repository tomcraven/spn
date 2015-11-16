#include "draw/TexturePool.h"
#include "draw/Draw.h"
#include "core/Assert.h"

#include <string.h>
#include <sdl_image.h>

namespace
{
	draw::TexturePool instance;
	const uint32_t kMaxTextures = 128;

	struct TexturePath
	{
		SDL_Texture* texture;
		const char* path;
	};
	TexturePath textures[kMaxTextures];
	uint32_t numTextures = 0;
}

namespace draw
{
	TexturePool& TexturePool::get()
	{
		return instance;
	}

	SDL_Texture* TexturePool::loadTexture( const char* path )
	{
		for ( uint32_t i = 0; i < numTextures; ++i )
		{
			if ( strcmp( path, textures[i].path ) == 0 )
			{
				return textures[i].texture;
			}
		}

		TexturePath& texturePath = textures[numTextures];
		texturePath.path = path;

		SDL_Surface* imageSurface = IMG_Load( path );
		VALIDATE_AND_RETURN( imageSurface, 0 );

		texturePath.texture = draw::Draw::get().createTextureFromSurface( imageSurface );
		VALIDATE_AND_RETURN( texturePath.texture, 0 );
		++numTextures;

		SDL_FreeSurface( imageSurface );

		return texturePath.texture;
	}

	bool TexturePool::shutdown()
	{
		for ( uint32_t i = 0; i < numTextures; ++i )
		{
			SDL_DestroyTexture( textures[i].texture );
		}

		return true;
	}
}