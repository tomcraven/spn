#ifndef COMPONENT_RENDERTEXTURE_H
#define COMPONENT_RENDERTEXTURE_H

#include "component/IComponent.h"
#include "component/IRender.h"
#include "component/Texture.h"

class CIw2DImage;

namespace component
{
	class Position;
	class Rotation;
	class Scale;

	class RenderTexture : public IComponent
	{
	public:
		void setTexture( Texture* texture );

	public: // IRender
		bool render( const Position& p, const Rotation& r, const Scale& s );

	public: // IComponent
		virtual bool init( ComponentEntity* entity );
		virtual uint32_t getType();

	private:
		Texture* texture;
	};
}

#endif