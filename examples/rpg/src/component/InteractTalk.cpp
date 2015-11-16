#include "component/InteractTalk.h"
#include "core/Assert.h"

namespace
{
	class NullConsumer : public component::InteractTalk::Consumer
	{
	public: // component::InteractTalk::Consumer
		bool onTalk( talk::Conversation* text )
		{
			return true;
		}
	};
}

namespace component
{
	InteractTalk::InteractTalk()
	{
		setConsumer( 0 );
	}

	void InteractTalk::setConsumer( Consumer* inConsumer )
	{
		if ( inConsumer )
		{
			consumer = inConsumer;
		}
		else
		{
			static NullConsumer nullConsumer;
			consumer = &nullConsumer;
		}
	}

	bool InteractTalk::go()
	{
		VALIDATE( consumer->onTalk( &( conversation[ 0 ] ) ) );
		return true;
	}

	bool InteractTalk::initComponent( ComponentEntity* entity )
	{
		conversation[0].talkText = "ey up there laddy, this is a test";
		conversation[0].numResponses = 1;
		conversation[0].responses[0].responseText = "orly?";
		conversation[0].responses[0].next = &( conversation[1] );
		
		conversation[1].talkText = "yarly, can you output all this shit correctly?";
		conversation[1].numResponses = 1;
		conversation[1].responses[0].responseText = "yup";
		conversation[1].responses[0].next = &( conversation[2] );
		
		conversation[2].talkText = "shit... fair enough then :)";
		conversation[2].numResponses = 1;
		conversation[2].responses[0].responseText = "ayyyylmao";

		return true;
	}
}