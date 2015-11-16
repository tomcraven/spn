#ifndef COMPONENT_TEXTURE_H
#define COMPONENT_TEXTURE_H

#include "component/IComponent.h"

struct SDL_Texture;

namespace component
{
	class Dimensions;
	class ComponentEntity;

	class Texture : public IComponent
	{
	public:
		Texture();

		void setTexturePath( const char* path );
		SDL_Texture* getTexture();

		uint32_t getWidth();
		uint32_t getHeight();

	public: // Component
		virtual uint32_t getType();
		virtual bool initComponent( ComponentEntity* entity );

	private:
		Dimensions *dimensions;
		SDL_Texture* texture;

		int width, height;
	};
}

#endif