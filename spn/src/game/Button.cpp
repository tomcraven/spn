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

	uint32_t generateUniqueButtonId()
	{
		static uint32_t id = 0;
		return id++;
	}
}

namespace game
{
	Button::Button() : id( generateUniqueButtonId() ), consumer( &nullButtonConsumer )
	{
		attach( &c );
		attach( &p );
		attach( &t );
		attach( &d );
		attach( &r );
		attach( &rot );
	}

	void Button::setConsumer( Consumer* inConsumer )
	{
		if ( inConsumer )
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
		VALIDATE( consumer->onButtonConsumerClick( id ) );
		return true;
	}

	const uint32_t Button::getId()
	{
		return id;
	}

	bool Button::render()
	{
		VALIDATE( r.render( p, rot ) );
		return true;
	}
}