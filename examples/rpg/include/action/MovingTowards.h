#ifndef ACTION_MOVINGTOWARDS_H
#define ACTION_MOVINGTOWARDS_H

#include "action/IAction.h"
#include "component/Position.h"

namespace component
{
	class ComponentEntity;
	class Velocity;
}

namespace action
{
	class MovingTowards : public IAction
	{
	public:
		MovingTowards();
		bool init( component::ComponentEntity* entity, const component::Position& end );
		bool init( component::Position* position, 
			component::Velocity* velocity, 
			const component::Position& end );

		class Consumer
		{
		public:
			virtual bool onActionFinished( MovingTowards& action ) = 0;
		};
		void setConsumer( Consumer* consumer );

	public: // IAction
		virtual bool update();

	private:
		bool initInternal( const component::Position& end );

	private:
		component::Position destination;

		typedef bool( *CompletedMovement )( float, float ); 
		CompletedMovement xAxisMovementCompletedFunc;
		CompletedMovement yAxisMovementCompletedFunc;

		component::Position* entityPosition;
		component::Velocity* entityVelocity;

		component::ComponentEntity* entity;

		Consumer* consumer;
	};
}

#endif