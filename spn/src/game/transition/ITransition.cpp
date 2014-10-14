#include "game/transition/ITransition.h"
#include "core/Algorithm.h"
#include "core/Assert.h"
#include "draw/Draw.h"
#include "draw/ScopedColour.h"

namespace
{
	class NullTransitionConsumer : public game::transition::ITransition::IConsumer
	{
	public:
		bool onTransitionComplete( uint32_t transitionId )
		{
			return true;
		}
	};

	uint32_t generateUniqueTransitionId()
	{
		static uint32_t id = 0;
		return id++;
	}
}

namespace game { namespace transition
{
	ITransition::ITransition()
	{
		setConsumer( 0 );
		id = generateUniqueTransitionId();
	}

	ITransition::~ITransition()
	{
	}

	bool ITransition::setConsumer( ITransition::IConsumer* inConsumer )
	{
		if ( inConsumer )
		{
			consumer = inConsumer;
		}
		else
		{
			static NullTransitionConsumer nullTransitionConsumer;
			consumer = &nullTransitionConsumer;
		}

		return true;
	}
}
}