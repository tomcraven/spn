#include "draw/TexturePool.h"
#include "core/Assert.h"

#include <IwMaterial.h>

namespace
{
	draw::TexturePool instance;

	const uint32_t kMaxTextures = 128;

	struct TexturePath
	{
		CIw2DImage* texture;
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

	CIw2DImage* TexturePool::loadTexture( const char* path )
	{
		CHECK_AND_RETURN( numTextures != kMaxTextures, 0 );

		for ( uint32_t i = 0; i < numTextures; ++i )
		{
			if ( strcmp( path, textures[i].path ) == 0 )
			{
				return textures[i].texture;
			}
		}

		TexturePath& texturePath = textures[numTextures];
		texturePath.path = path;
		texturePath.texture = Iw2DCreateImage( path );
		++numTextures;
		
		texturePath.texture->GetMaterial()->SetFiltering( false );

		Iw2DSetUseMipMapping( false );

		return texturePath.texture;
	}

	bool TexturePool::shutdown()
	{
		for ( uint32_t i = 0; i < numTextures; ++i )
		{
			delete textures[i].texture;
		}

		return true;
	}
}