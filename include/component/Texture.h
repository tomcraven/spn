#ifndef COMPONENT_TEXTURE_H
#define COMPONENT_TEXTURE_H

#include "component/IComponent.h"

class CIw2DImage;

namespace component
{
	class Dimensions;

	class Texture : public IComponent
	{
	public:
		Texture();

		void setTexture( const char* path, Dimensions& d );
		CIw2DImage* getTexture();

		uint32_t getWidth();
		uint32_t getHeight();

	public: // Component
		virtual uint32_t getType();

	private:
		CIw2DImage* texture;
	};
}

#endif