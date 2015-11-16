#include "component/Wander.h"
#include "component/Position.h"
#include "component/Dimensions.h"
#include "component/Velocity.h"
#include "component/ComponentEntity.h"
#include "core/Assert.h"
#include "core/Rand.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	Wander::Wander() : currentAction( &nullAction )
	{
	}

	bool Wander::init( const Config& inConfig )
	{
		config = inConfig;
		wanderTimer.setTimerExpiredListener( this );
		movingAction.setConsumer( this );

		startTimer();

		return true;
	}

	bool Wander::initComponent( ComponentEntity* entity )
	{
		VALIDATE( entity->getComponent< Position >( &position ) );
		VALIDATE( entity->getComponent< Velocity >( &velocity ) );
		VALIDATE( entity->getComponent< Dimensions >( &dimensions ) );
		return true;
	}

	bool Wander::update( ComponentEntity* componentEntity, float timeStep )
	{
		VALIDATE( currentAction->update() );
		VALIDATE( wanderTimer.update( timeStep ) );
		return true;
	}

	uint32_t Wander::getType()
	{
		return typeId;
	}

	bool Wander::onTimerExpired( uint32_t id )
	{
		VALIDATE( id == wanderTimer.getId() );

		if ( currentAction != &nullAction )
		{
			ASSERT( false );
			return true;
		}

		component::Position randomPosition;
		const math::Rect< int32_t >& wanderRect = config.maxSingleMovementRect;
		do
		{
			int32_t randomXPosition = static_cast< uint32_t >( core::random::range(
				position->x + wanderRect.x, position->x + wanderRect.w ) );
			int32_t randomYPosition = static_cast< uint32_t >( core::random::range(
				position->y + wanderRect.y, position->y + wanderRect.h ) );

			randomPosition.set( randomXPosition, randomYPosition );
		} while ( !positionIsWalkable( randomPosition ) );

		VALIDATE( moveTo( randomPosition ) );

		return true;
	}

	bool Wander::onActionFinished( action::MovingTowards& movingAction )
	{
		int32_t targetX, targetY;
		if( currentPath.peek( targetX, targetY ) )
		{
			VALIDATE( currentPath.pop() );
			VALIDATE( movingAction.init( position, velocity, 
				component::Position( targetX, targetY ) ) );
		}
		else
		{
			currentAction = &nullAction;
			startTimer();
		}

		return true;
	}

	bool Wander::moveTo( const component::Position& pos )
	{
		VALIDATE( currentPath.clear() );
	
		currentAction = &movingAction;

		VALIDATE( config.level->createPathTo( *position, pos, currentPath ) );
		VALIDATE( onActionFinished( movingAction ) );

		return true;
	}

	bool Wander::positionIsWalkable( const component::Position& pos )
	{
		CHECK( pos.x >= config.wanderRect.x );
		CHECK( pos.y >= config.wanderRect.y );
		CHECK( pos.x <= config.wanderRect.w );
		CHECK( pos.y <= config.wanderRect.h );
		return config.level->positionIsWalkable( pos );
	}

	void Wander::startTimer()
	{
		wanderTimer.setTimeout( core::random::range(
			config.delaySecondsMin, config.delaySecondsMax ) );
	}
}