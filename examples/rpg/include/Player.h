#ifndef PLAYER_H
#define PLAYER_H

#include "component/ComponentEntity.h"
#include "component/Texture.h"
#include "component/RenderTexture.h"
#include "component/Position.h"
#include "component/Velocity.h"
#include "component/Speed.h"
#include "component/Dimensions.h"
#include "Path.h"
#include "action/MovingTowards.h"
#include "action/Null.h"

class Level;

class Player : 
	public component::ComponentEntity,
	public action::MovingTowards::Consumer
{
public:
	Player();

	bool moveTo( int32_t x, int32_t y );

	struct Config
	{
		Level* level;
	};
	bool init( const Config& config );
	
public: // action::MovingTowards::Consumer
	virtual bool onActionFinished( action::MovingTowards& movingAction );

public: // game::Entity
	virtual bool shutdown();
	virtual bool update( float timeStep );
	virtual bool render();

private:
	virtual bool init();

private:
	component::Texture texture;
	component::RenderTexture r;
	component::Position position;
	component::Dimensions d;
	component::Velocity v;
	component::Speed speed;

	action::IAction* currentAction;
	action::MovingTowards movingAction;
	action::Null nullAction;

	Config config;
	Path currentPath;
};

#endif