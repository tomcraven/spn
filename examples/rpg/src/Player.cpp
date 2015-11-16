#include "Player.h"
#include "core/Assert.h"
#include "Level.h"

Player::Player() : speed( 60.0f ), currentAction( &nullAction )
{
	attach( &texture );
	attach( &r );
	attach( &position );
	attach( &d );
	attach( &v );
	attach( &speed );
}

bool Player::moveTo( int32_t x, int32_t y )
{
	CHECK( config.level->positionIsWalkable( component::Position( x, y ) ) );

	VALIDATE( currentPath.clear() );
	
	if ( config.level->createPathTo( position, component::Position( x, y ), currentPath ) )
	{
		VALIDATE( onActionFinished( movingAction ) );
		currentAction = &movingAction;
	}

	return true;
}

bool Player::onActionFinished( action::MovingTowards& movingAction )
{
	int32_t targetX, targetY;
	if( currentPath.peek( targetX, targetY ) )
	{
		VALIDATE( currentPath.pop() );
		VALIDATE( movingAction.init( this, 
			component::Position( targetX, targetY ) ) );
	}
	else
	{
		currentAction = &nullAction;
	}

	return true;
}

bool Player::init()
{
	// Should use the init with config
	return false;
}

bool Player::init( const Config& inConfig )
{
	VALIDATE( component::ComponentEntity::init() );

	texture.setTexturePath( "textures/player.png" );
	movingAction.setConsumer( this );

	config = inConfig;
	
	return true;
}

bool Player::shutdown()
{
	VALIDATE( component::ComponentEntity::shutdown() );
	return true;
}

bool Player::update( float timeStep )
{
	VALIDATE( component::ComponentEntity::update( timeStep ) );

	VALIDATE( currentAction->update() );

	return true;
}

bool Player::render()
{
	VALIDATE( r.render( position ) );
	return true;
}