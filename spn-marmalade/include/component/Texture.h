#ifndef COMPONENT_TEXTURE_H
#define COMPONENT_TEXTURE_H

#include "component/IComponent.h"

class CIw2DImage;

namespace component
{
	class Dimensions;
	class ComponentEntity;

	class Texture : public IComponent
	{
	public:
		Texture();

		void setTexturePath( const char* path );
		CIw2DImage* getTexture();

		uint32_t getWidth();
		uint32_t getHeight();

	public: // Component
		virtual uint32_t getType();
		virtual bool init( ComponentEntity* entity );

	private:
		CIw2DImage* texture;
		Dimensions *dimensions;
	};
}

#endif