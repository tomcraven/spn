#ifndef COMPONENT_WANDER_H
#define COMPONENT_WANDER_H

#include "component/IComponent.h"
#include "math/Rect.h"
#include "async/Timer.h"
#include "action/IAction.h"
#include "action/MovingTowards.h"
#include "action/Null.h"
#include "Level.h"
#include "Path.h"

namespace component
{
	class Position;
	class Velocity;
	class Dimensions;

	class Wander : 
		public IComponent,
		public async::Timer::IExpiredListener,
		public action::MovingTowards::Consumer
	{
	public:
		Wander();

		struct Config
		{
			Config() : wanderRect( 0, 0, 1, 1 ), 
				maxSingleMovementRect( 0, 0, 1, 1 ),
				delaySecondsMin( 1.0f ),
				delaySecondsMax( 1.0f ),
				level( 0 )
			{}

			math::Rect< uint32_t > wanderRect;
			math::Rect< int32_t > maxSingleMovementRect;
			float delaySecondsMin, delaySecondsMax;
			Level* level;
		};

		bool init( const Config& config );

	public: // Component
		virtual bool initComponent( ComponentEntity* componentEntity );
		virtual bool update( ComponentEntity* componentEntity, float timeStep );
		virtual uint32_t getType();

	public: // async::Timer::IExpiredListener
		virtual bool onTimerExpired( uint32_t id );

	public: // action::MovingTowards::Consumer
		bool onActionFinished( action::MovingTowards& movingAction );

	private:
		bool moveTo( const component::Position& pos );
		bool positionIsWalkable( const component::Position& pos );
		void startTimer();

	private:
		Position* position;
		Velocity* velocity;
		Dimensions* dimensions;

		Config config;
		
		async::Timer wanderTimer;
		
		action::IAction* currentAction;
		action::MovingTowards movingAction;
		action::Null nullAction;
		
		Path currentPath;
	};
}

#endif