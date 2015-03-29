#include "component/RenderTexture.h"
#include "component/Position.h"
#include "component/Rotation.h"
#include "component/Scale.h"
#include "component/ComponentEntity.h"
#include "core/Assert.h"
#include "draw/TexturePool.h"
#include "draw/Draw.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	bool RenderTexture::render( const Position& p, const Rotation& rot, const Scale& s )
	{
		draw::Draw::get().blit( texture, p.x, p.y, s.scale, rot.r );
		return true;
	}

	bool RenderTexture::render( const Position& p, const Rotation& rot )
	{
		draw::Draw::get().blit( texture, p.x, p.y, 1.0f, rot.r );
		return true;
	}

	bool RenderTexture::init( ComponentEntity* entity )
	{
		VALIDATE( entity->getComponent< Texture >( &texture ) );
		return true;
	}

	uint32_t RenderTexture::getType()
	{
		return typeId;
	}
} // component