#ifndef COMPONENT_INTERACTTALK_H
#define COMPONENT_INTERACTTALK_H

#include "component/InteractBase.h"
#include "talk/Conversation.h"
#include "talk/Conversation.h"

namespace component
{
	class InteractTalk : public InteractBase
	{
	public:
		InteractTalk();

		class Consumer
		{
		public:
			virtual bool onTalk( talk::Conversation* text ) = 0;
		};

		void setConsumer( Consumer* consumer );

	public: // InteractBase
		virtual bool go();

		virtual bool initComponent( ComponentEntity* entity );

	private:
		Consumer* consumer;

		talk::Conversation conversation[3];
	};
}

#endif