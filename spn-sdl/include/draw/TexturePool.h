#ifndef DRAW_TEXTUREPOOL_H
#define DRAW_TEXTUREPOOL_H

struct SDL_Texture;

namespace draw
{
	class TexturePool
	{
	public:
		static TexturePool& get();
		SDL_Texture* loadTexture( const char* path );

		bool shutdown();
	};
}

#endif