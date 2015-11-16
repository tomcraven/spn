#include "InteractiveNPC.h"
#include "core/Assert.h"
#include "NpcPopulation.h"

InteractiveNPC::InteractiveNPC()
{
	attach( &c );
	attach( &interact );
}

bool InteractiveNPC::init( const Config& inConfig )
{
	VALIDATE( NPC::init() );
	c.setConsumer( this );
	config = inConfig;

	return true;
}

bool InteractiveNPC::onClickableConsumerClick()
{
	VALIDATE( config.consumer->onNpcClicked( this ) );
	return true;
}