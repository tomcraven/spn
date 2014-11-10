#include "City.h"
#include "draw/Colour.h"
#include "draw/Draw.h"

namespace
{
	const char* buildingPaths[] =
	{
		"textures/city1.png",
		"textures/city2.png",
		"textures/city3.png"
	};
	const char* getRandomBuildingPath()
	{
		const uint32_t numBuildingPaths = sizeof( buildingPaths ) / sizeof( const char* );
		return buildingPaths[ rand() % numBuildingPaths ];
	}

	const uint32_t kColours[] =
	{
		draw::colour::colourFromRGBA( 215, 83, 40 ),
		draw::colour::colourFromRGBA( 215, 113, 40 ),
		draw::colour::colourFromRGBA( 215, 133, 40 )
	};
	uint32_t getRandomColour()
	{
		const uint32_t numColours = sizeof( kColours ) / sizeof( uint32_t );
		return kColours[ rand() % numColours ];
	}
}

bool City::init( uint32_t numConcurrentBuildings )
{
	VALIDATE( buildingPool.init( numConcurrentBuildings ) );
	buildingCreateTimer.setRepeat( true );
	buildingCreateTimer.setTimerExpiredListener( this );
	buildingCreateTimer.setTimeout( 1.0f );
	return true;
}

bool City::shutdown()
{
	VALIDATE( buildingPool.shutdown() );
	return true;
}

bool City::update( float timeStepSeconds )
{
	std::vector< Building* >::iterator buildingIter;
	for ( buildingIter = buildings.begin(); buildingIter != buildings.end(); ++buildingIter )
	{
		VALIDATE( ( *buildingIter )->update( timeStepSeconds ) );
	}

	VALIDATE( buildingCreateTimer.update( timeStepSeconds ) );

	return true;
}

bool City::render()
{
	std::vector< Building* >::iterator buildingIter;
	for ( buildingIter = buildings.begin(); buildingIter != buildings.end(); ++buildingIter )
	{
		VALIDATE( ( *buildingIter )->render() );
	}

	return true;
}

bool City::createBuilding()
{
	Building* newBuilding = buildingPool.alloc();
	VALIDATE( newBuilding );
	newBuilding->init( getRandomColour(), getRandomBuildingPath() );

	component::Dimensions* dimensions = newBuilding->getComponent< component::Dimensions >();
	VALIDATE( dimensions );
	USE_COMPONENT_PTR( newBuilding, 
		component::Position, 
		set( 
			draw::Draw::getScreenWidth(), 
			draw::Draw::getScreenHeight() - dimensions->height + ( rand() % 20 ) ) );
	USE_COMPONENT_PTR( newBuilding, component::Velocity, set( -20.0f - ( rand() % 20 ), 0.0f ) );
	USE_COMPONENT_PTR( newBuilding, component::WindowExitCollision, setConsumer( this ) );

	buildings.push_back( newBuilding );

	return true;
}

bool City::onTimerExpired( uint32_t id )
{
	ASSERT( id == buildingCreateTimer.getId() );
	VALIDATE( createBuilding() );
	return true;
}

bool City::onWindowExit( component::ComponentEntity* entity, bool left, bool right, bool top, bool bottom )
{
	ASSERT( !right );
	ASSERT( !top );
	ASSERT( !bottom );

	if ( left )
	{
		Building* building = dynamic_cast< Building* >( entity );
		ASSERT( building );
		buildingPool.free( building );

		std::vector< Building* >::iterator buildingIter;
		buildingIter = std::find( buildings.begin(), buildings.end(), entity );
		ASSERT( buildingIter != buildings.end() );
		buildings.erase( buildingIter );
	}

	return true;
}