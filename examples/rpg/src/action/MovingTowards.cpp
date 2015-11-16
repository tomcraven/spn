#include "action/MovingTowards.h"
#include "component/Position.h"
#include "component/Velocity.h"
#include "component/ComponentEntity.h"
#include "core/Assert.h"
#include "core/Algorithm.h"

namespace
{
	bool greaterThan( float a, float b )
	{
		return a >= b;
	}

	bool lessThan( float a, float b )
	{
		return a <= b;
	}

	bool returnFalse( float a, float b )
	{
		return false;
	}

	bool returnTrue( float a, float b )
	{
		return true;
	}
	
	class NullConsumer : public action::MovingTowards::Consumer
	{
	public:
		bool onActionFinished( action::MovingTowards& action )
		{
			return true;
		}
	};
}

namespace action
{
	MovingTowards::MovingTowards() : 
		xAxisMovementCompletedFunc( &returnFalse ),
		yAxisMovementCompletedFunc( &returnFalse ),
		entityPosition( 0 ), entityVelocity( 0 ), entity( 0 ),
		consumer( 0 )
	{
		setConsumer( 0 );
	}

	bool MovingTowards::init( component::ComponentEntity* entity, const component::Position& end )
	{
		VALIDATE( entity->getComponent< component::Position >( &entityPosition ) );
		VALIDATE( entity->getComponent< component::Velocity >( &entityVelocity ) );

		CHECK( initInternal( end ) );

		return true;
	}

	bool MovingTowards::init( component::Position* position, 
		component::Velocity* velocity, 
		const component::Position& end )
	{
		entityPosition = position;
		entityVelocity = velocity;
		CHECK( initInternal( end ) );
		return true;
	}

	bool MovingTowards::initInternal( const component::Position& end )
	{
		destination = end;

		if ( core::algorithm::floatEquals( entityPosition->x, end.x ) )
		{
			xAxisMovementCompletedFunc = &returnTrue;
		}
		else if ( entityPosition->x < end.x )
		{
			xAxisMovementCompletedFunc = &greaterThan;
		}
		else if ( entityPosition->x > end.x )
		{
			xAxisMovementCompletedFunc = &lessThan;
		}
		
		if ( core::algorithm::floatEquals( entityPosition->y, end.y ) )
		{
			yAxisMovementCompletedFunc = &returnTrue;
		}
		else if ( entityPosition->y < end.y )
		{
			yAxisMovementCompletedFunc = &greaterThan;
		}
		else if ( entityPosition->y > end.y )
		{
			yAxisMovementCompletedFunc = &lessThan;
		}
		
		entityVelocity->x = destination.x - entityPosition->x;
		entityVelocity->y = destination.y - entityPosition->y;
		entityVelocity->unit();

		return true;
	}

	void MovingTowards::setConsumer( Consumer* inConsumer )
	{
		if ( consumer )
		{
			consumer = inConsumer;
		}
		else
		{
			static NullConsumer nullConsumer;
			consumer = &nullConsumer;
		}
	}

	bool MovingTowards::update()
	{
		if ( xAxisMovementCompletedFunc( entityPosition->x, destination.x ) &&
			yAxisMovementCompletedFunc( entityPosition->y, destination.y ) )
		{
			entityPosition->set( destination );
			entityVelocity->set( 0, 0 );

			VALIDATE( consumer->onActionFinished( *this ) );
		}

		return true;
	}
}