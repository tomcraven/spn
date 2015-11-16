#ifndef NPCPOPULATION_H
#define NPCPOPULATION_H

#include "WanderingNPC.h"
#include "InteractiveNPC.h"

class Level;

class NpcPopulation : public InteractiveNPC::Consumer
{
public:
	NpcPopulation();

	struct Config
	{
		Config() : level( 0 ), talkConsumer( 0 )
		{}

		Level* level;
		component::InteractTalk::Consumer* talkConsumer;
	};

	bool init( const Config& config );
	bool shutdown();
	bool update( float timeStep );
	bool render();

	NPC* getClickedNpc();

public: // InteractiveNPC::Consumer
	bool onNpcClicked( NPC* npc );

private:
	static const uint32_t kNumWanderingNpcs = 10;
	WanderingNPC wanderingNpcs[kNumWanderingNpcs];
	InteractiveNPC interactiveNpc;

	NPC* clickedNpc;
};

#endif