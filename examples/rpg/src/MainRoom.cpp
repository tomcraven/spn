#include "MainRoom.h"
#include "core/Assert.h"
#include "draw/Draw.h"
#include "draw/ColourConstants.h"
#include "tween/TweenFactory.h"
#include "math/Rect.h"
#include "core/Rand.h"
#include "math/Intersect.h"
#include "component/InteractBase.h"

#include <stdio.h>

bool MainRoom::init()
{
	draw::Draw::get().setScale( 2.0f );

	VALIDATE( initLevel() );

	NpcPopulation::Config npcPopulationConfig;
	npcPopulationConfig.level = &level;
	npcPopulationConfig.talkConsumer = &talkDisplay;
	VALIDATE( npcPopulation.init( npcPopulationConfig ) );

	Player::Config playerConfig;
	playerConfig.level = &level;
	VALIDATE( player.init( playerConfig ) );
	USE_COMPONENT( player, component::Position, set( 80, 80 ) );
	VALIDATE( player.getComponent< component::Position >( &viewportCentrePosition ) );
	
	VALIDATE( input::Input::get().addConsumer( this ) );

	return true;
}

bool MainRoom::initLevel()
{
	VALIDATE( level.setTileSheet( "textures/tileset.png" ) );
	VALIDATE( level.setTileMap( "pyxel/1.txt" ) );
	VALIDATE( level.setCollisionMap( "pyxel/1_collision.txt" ) );
	return true;
}

bool MainRoom::initNpcPopulation()
{
	return true;
}

bool MainRoom::shutdown()
{
	VALIDATE( Room::shutdown() );

	VALIDATE( player.shutdown() );
	VALIDATE( npcPopulation.shutdown() );
	VALIDATE( level.shutdown() );

	return true;
}

bool MainRoom::update()
{
	VALIDATE( Room::update() );

	const float kTimeStep = Room::getTimeStepSeconds();
	VALIDATE( npcPopulation.update( kTimeStep ) );
	VALIDATE( player.update( kTimeStep ) );

	component::Position centre( *viewportCentrePosition );
	centre.x += 8;
	centre.y += 8;
	draw::Draw::get().setViewportCentre( &centre );

	return true;
}

bool MainRoom::render()
{
	draw::Draw& draw = draw::Draw::get();
	VALIDATE( draw.clear( 0xFF333333 ) );

	VALIDATE( level.render() );
	VALIDATE( npcPopulation.render() );
	VALIDATE( player.render() );
	VALIDATE( talkDisplay.render() );

	VALIDATE( draw.flip() );
	return true;
}

bool MainRoom::onInputConsumerButtonDown( uint32_t x, uint32_t y )
{
	NPC* clickedNpc = npcPopulation.getClickedNpc();
	if ( clickedNpc )
	{
		VALIDATE( clickedNpc->getComponent< component::InteractBase >()->go() );
	}
	else
	{
		float worldX, worldY;
		draw::Draw::get().convertScreenToWorldCoorinatesA( x, y, worldX, worldY );

		CHECK( player.moveTo( 
			static_cast< int32_t >( worldX ), 
			static_cast< int32_t >( worldY ) ) );
	}

	return true;
}