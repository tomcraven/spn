#include "NPC.h"
#include "core/Assert.h"
#include "Level.h"
#include "core/Rand.h"

NPC::NPC()
{
	attach( &texture );
	attach( &r );
	attach( &position );
	attach( &d );
}

bool NPC::init()
{
	VALIDATE( component::ComponentEntity::init() );
	texture.setTexturePath( "textures/player.png" );

	return true;
}

bool NPC::render()
{
	VALIDATE( r.render( position ) );
	return true;
}