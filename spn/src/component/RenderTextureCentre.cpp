#include "component/RenderTextureCentre.h"
#include "component/Position.h"
#include "component/Rotation.h"
#include "component/Scale.h"
#include "component/ComponentEntity.h"
#include "component/Dimensions.h"
#include "core/Assert.h"
#include "draw/TexturePool.h"
#include "draw/Draw.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	RenderTextureCentre::RenderTextureCentre() : centreWidth( 0.0f ), centreHeight( 0.0f )
	{
	}

	bool RenderTextureCentre::render( const Position& p, const Rotation& rot, const Scale& s )
	{
		draw::Draw::get().blit( texture, 
			p.x - dimensions->halfWidth, p.y - dimensions->halfHeight, 
			s.scale, rot.r );
		return true;
	}

	bool RenderTextureCentre::render( const Position& p, const Rotation& rot )
	{
		draw::Draw::get().blit( texture, 
			p.x - dimensions->halfWidth, p.y - dimensions->halfHeight, 
			1.0f, rot.r );
		return true;
	}

	bool RenderTextureCentre::render( const Position& p )
	{
		draw::Draw::get().blit( texture, 
			p.x - dimensions->halfWidth, p.y - dimensions->halfHeight, 
			1.0f, 0.0f );
		return true;
	}

	bool RenderTextureCentre::initComponent( ComponentEntity* entity )
	{
		VALIDATE( entity->getComponent< Texture >( &texture ) );
		VALIDATE( entity->getComponent< Dimensions >( &dimensions ) );

		return true;
	}

	uint32_t RenderTextureCentre::getType()
	{
		return typeId;
	}
} // component