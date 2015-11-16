#ifndef TALK_TALKSPLIT_H
#define TALK_TALKSPLIT_H

#include "core/Types.h"
#include "core/String.h"
#include "core/Platform.h"

namespace talk
{
	struct Line
	{
		core::String text;
		uint32_t width;
	};

	template< int kSize = 10 >
	class TalkSplit
	{
	public:
		Line* splitPixels( const char* inText, uint32_t maxPixelWidth, uint32_t& outNumLines )
		{
			static uint32_t spaceWidth = draw::Draw::get().getTextWidth( " " );

			core::String stringText = inText;
			char* text = stringText.str();

			char* context = 0;
			char* word = STRTOK_S( text, " ", &context );
			
			lines[ outNumLines ].width = 0;
			lines[ outNumLines ].text = "";
			while( word )
			{
				uint32_t wordWidth = draw::Draw::get().getTextWidth( word );
				lines[ outNumLines ].width += wordWidth;
				
				if ( lines[ outNumLines ].text.size() != 1 )
				{
					lines[ outNumLines ].width += spaceWidth;
				}

				if ( lines[ outNumLines ].width > maxPixelWidth )
				{
					lines[ outNumLines ].width -= wordWidth;
					if ( lines[ outNumLines ].text.size() != 1 )
					{
						lines[ outNumLines ].width -= spaceWidth;
					}

					++outNumLines;
					lines[ outNumLines ].text = "";
					lines[ outNumLines ].width = wordWidth;
				}
				
				if ( lines[ outNumLines ].text.size() != 1 )
				{
					lines[ outNumLines ].text += " ";
				}

				lines[ outNumLines ].text += word;
				
				word = STRTOK_S( 0, " ", &context );
			}

			outNumLines++;

			return lines;
		}

	private:
		Line lines[ kSize ];
	};
}

#endif