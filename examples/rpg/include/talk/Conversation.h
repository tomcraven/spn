#ifndef TALK_CONVERSATION_H
#define TALK_CONVERSATION_H

#include "core/String.h"

namespace talk
{
	struct Conversation
	{
		Conversation() : numResponses( 0 )
		{
		}

		core::String talkText;
		
		struct Response
		{
			Response() : next( 0 )
			{}

			core::String responseText;
			Conversation* next;
		};

		static const int kMaxNumResponses = 5;

		uint32_t numResponses;
		Response responses[ kMaxNumResponses ];
	};
}

#endif