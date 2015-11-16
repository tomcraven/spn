#include "WanderingNPC.h"
#include "core/Assert.h"
#include "Level.h"
#include "core/Rand.h"

WanderingNPC::WanderingNPC() : speed( 60.0f )
{
	attach( &v );
	attach( &speed );
	attach( &w );
}

bool WanderingNPC::init( const Config& config )
{
	VALIDATE( NPC::init() );
	VALIDATE( w.init( config.wanderConfig ) );
	speed.set( config.speed );

	return true;
}