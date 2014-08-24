#include "game/Button.h"
#include "core/Assert.h"

namespace
{
	class NullButtonConsumer : public game::Button::Consumer
	{
	public:
		bool onButtonConsumerClick( uint32_t id )
		{
			return true;
		}
	};

	NullButtonConsumer nullButtonConsumer;
}

namespace game
{
	Button::Button( uint32_t inId ) : id( inId ), consumer( &nullButtonConsumer )
	{
	}

	void Button::setConsumer( Consumer* inConsumer )
	{
		if ( consumer )
		{
			consumer = inConsumer;
		}
		else
		{
			consumer = &nullButtonConsumer;
		}
	}

	bool Button::onClickableConsumerClick()
	{
		CHECK( consumer->onButtonConsumerClick( id ) );
		return true;
	}
}