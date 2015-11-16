#ifndef WANDERINGNPC_H
#define WANDERINGNPC_H

#include "NPC.h"
#include "math/Rect.h"
#include "async/Timer.h"
#include "action/MovingTowards.h"
#include "action/Null.h"
#include "Path.h"
#include "component/Velocity.h"
#include "component/Speed.h"
#include "component/Wander.h"

class Level;

class WanderingNPC : public NPC
{
public:
	WanderingNPC();

	struct Config
	{
		Config() : speed( 60.0f )
		{
		}

		component::Wander::Config wanderConfig;
		float speed;
	};
	
	bool init( const Config& config );

private:
	virtual bool init() { return false; }

	component::Wander w;
	component::Velocity v;
	component::Speed speed;
};

#endif