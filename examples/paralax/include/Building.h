#ifndef BUILDING_H
#define BUILDING_H

#include "component/ComponentEntity.h"
#include "component/Position.h"
#include "component/Velocity.h"
#include "component/Texture.h"
#include "component/RenderTexture.h"
#include "component/Dimensions.h"
#include "component/WindowExitCollision.h"
#include "core/Assert.h"
#include "draw/ScopedColour.h"

class Building : public component::ComponentEntity
{
public:
	Building()
	{
		attach( &p );
		attach( &v );
		attach( &t );
		attach( &r );
		attach( &d );
		attach( &w );
	}

	bool init( uint32_t inColour, const char* texturePath )
	{
		VALIDATE( component::ComponentEntity::init() );

		t.setTexturePath( texturePath );
		colour = inColour;
		return true;
	}

	bool render()
	{
		draw::ScopedColour scopedColour( colour );
		VALIDATE( r.render( p ) );
		return true;
	}

private:
	component::Position p;
	component::Velocity v;
	component::Texture t;
	component::RenderTexture r;
	component::Dimensions d;
	component::WindowExitCollision w;
	uint32_t colour;
};

#endif