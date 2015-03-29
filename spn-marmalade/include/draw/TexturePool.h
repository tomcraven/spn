#ifndef DRAW_TEXTUREPOOL_H
#define DRAW_TEXTUREPOOL_H

#include "Iw2D.h"

namespace draw
{
	class TexturePool
	{
	public:
		static TexturePool& get();
		CIw2DImage* loadTexture( const char* path );

		bool shutdown();
	};
}

#endif