#ifndef TALKDISPLAY_H
#define TALKDISPLAY_H

#include "component/InteractTalk.h"
#include "async/Timer.h"
#include "core/String.h"

namespace talk
{
	struct Conversation;

	class TalkDisplay : public component::InteractTalk::Consumer
	{
	public:
		TalkDisplay();

	public: // component::IComponent
		bool render();

	public: // component::InteractTalk::Consumer
		virtual bool onTalk( Conversation* text );

	private:
		Conversation* currentConversation;
	};
}

#endif