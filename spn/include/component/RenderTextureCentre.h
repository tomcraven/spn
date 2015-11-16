#ifndef COMPONENT_RENDERTEXTURECENTRE_H
#define COMPONENT_RENDERTEXTURECENTRE_H

#include "component/IComponent.h"
#include "component/Texture.h"

namespace component
{
	class Position;
	class Rotation;
	class Scale;
	class Dimensions;

	class RenderTextureCentre : public IComponent
	{
	public:
		RenderTextureCentre();
		void setTexture( Texture* texture );
		
		bool render( const Position& p, const Rotation& r, const Scale& s );
		bool render( const Position& p, const Rotation& r );
		bool render( const Position& p );

	public: // IComponent
		virtual bool initComponent( ComponentEntity* entity );
		virtual uint32_t getType();

	private:
		Texture* texture;
		Dimensions* dimensions;

		float centreWidth, centreHeight;
	};
}

#endif