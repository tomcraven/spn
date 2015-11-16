#include "talk/TalkDisplay.h"
#include "core/Assert.h"
#include "talk/Conversation.h"
#include "draw/Draw.h"
#include "draw/ScopedColour.h"
#include "draw/ColourConstants.h"
#include "talk/TalkSplit.h"
#include "TextBox.h"

namespace talk
{
	TalkDisplay::TalkDisplay() : currentConversation( 0 )
	{
	}

	bool TalkDisplay::render()
	{
		if ( currentConversation )
		{
			const char* fullText = currentConversation->talkText.c_str();

			talk::TalkSplit< 10 > split;

			uint32_t numLines = 0;
			uint32_t maxPixelWidth = 64;
			talk::Line* lines = split.splitPixels( fullText, maxPixelWidth, numLines );

			TextBox tb;
			VALIDATE( tb.init( lines, numLines ) );
			VALIDATE( tb.render() );
		}

		return true;
	}

	bool TalkDisplay::onTalk( Conversation* conversation )
	{
		currentConversation = conversation;

		return true;
	}
}