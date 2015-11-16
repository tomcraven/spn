#ifndef INTERACTIVENPC_H
#define INTERACTIVENPC_H

#include "NPC.h"
#include "component/Clickable.h"
#include "component/InteractTalk.h"

class NpcPopulation;

class InteractiveNPC : 
	public NPC,
	public component::Clickable::Consumer
{
public:
	InteractiveNPC();

	class Consumer
	{
	public:
		virtual bool onNpcClicked( NPC* npc ) = 0;
	};

	struct Config
	{
		Consumer* consumer;
	};
	bool init( const Config& config );

public: // component::Clickable::Consumer
	bool onClickableConsumerClick();

private: // NPC
	virtual bool init() { return false; }

private:
	component::Clickable c;
	component::InteractTalk interact;

	Config config;
};

#endif