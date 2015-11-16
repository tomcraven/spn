#include "NpcPopulation.h"
#include "core/Assert.h"
#include "core/Rand.h"

NpcPopulation::NpcPopulation() : clickedNpc( 0 )
{
}

bool NpcPopulation::init( const Config& config )
{
	WanderingNPC::Config npcConfig;
	npcConfig.wanderConfig.delaySecondsMin = 0.0f;
	npcConfig.wanderConfig.delaySecondsMax = 3.0f;
	npcConfig.wanderConfig.level = config.level;
	npcConfig.wanderConfig.wanderRect.set( 0, 0, config.level->getWidth(), config.level->getHeight() );
	npcConfig.wanderConfig.maxSingleMovementRect.set( -64, -64, 64, 64 );
	for ( uint32_t i = 0; i < kNumWanderingNpcs; ++i )
	{
		npcConfig.speed = core::random::range( 10.0f, 40.0f );
		VALIDATE( wanderingNpcs[i].init( npcConfig ) );
		USE_COMPONENT( wanderingNpcs[i], component::Position, set( 96, 96 ) );
	}
	
	InteractiveNPC::Config interactiveNpcConfig;
	interactiveNpcConfig.consumer = this;
	VALIDATE( interactiveNpc.init( interactiveNpcConfig ) );
	USE_COMPONENT( interactiveNpc, component::Position, set( 96, 96 ) );
	USE_COMPONENT( interactiveNpc, component::InteractTalk, setConsumer( config.talkConsumer ) );

	return true;
}

bool NpcPopulation::shutdown()
{
	VALIDATE( interactiveNpc.shutdown() );

	for ( uint32_t i = 0; i < kNumWanderingNpcs; ++i )
	{
		VALIDATE( wanderingNpcs[i].shutdown() );
	}

	return true;
}

bool NpcPopulation::update( float timeStep )
{
	clickedNpc = 0;

	for ( uint32_t i = 0; i < kNumWanderingNpcs; ++i )
	{
		VALIDATE( wanderingNpcs[i].update( timeStep ) );
	}

	VALIDATE( interactiveNpc.update( timeStep ) );
	
	return true;
}

bool NpcPopulation::render()
{
	VALIDATE( interactiveNpc.render() );
	
	for ( uint32_t i = 0; i < kNumWanderingNpcs; ++i )
	{
		VALIDATE( wanderingNpcs[i].render() );
	}
	
	return true;
}

NPC* NpcPopulation::getClickedNpc()
{
	return clickedNpc;
}

bool NpcPopulation::onNpcClicked( NPC* npc )
{
	clickedNpc = npc;
	return true;
}