#include "TextBox.h"
#include "talk/TalkSplit.h"
#include "draw/Draw.h"
#include "draw/ScopedColour.h"
#include "draw/ColourConstants.h"

bool TextBox::init( talk::Line* inLines, uint32_t inNumLines )
{
	lines = inLines;
	numLines = inNumLines;

	return true;
}

bool TextBox::render()
{
	draw::Draw& draw = draw::Draw::get();

	uint32_t textHeight = draw.getTextHeight();
	uint32_t topLeftY = ( draw.getScreenHeight() / 2 ) - ( ( textHeight * numLines ) / 2 );

	uint32_t maxLineWidth = 0;
	for ( uint32_t i = 0; i < numLines; ++i )
	{
		if ( lines[i].width > maxLineWidth )
		{
			maxLineWidth = lines[i].width;
		}
	}

	uint32_t topLeftX = ( draw.getScreenWidth() / 2 ) - ( maxLineWidth / 2 );
	for ( uint32_t i = 0; i < numLines; ++i )
	{
		draw::ScopedColour scopedColour( draw::colour::colourFromRGBA( 123, 123, 123, 200 ) );
		draw.filledRect( topLeftX, topLeftY + ( textHeight * i ), maxLineWidth, textHeight );
	}
	
	for ( uint32_t i = 0; i < numLines; ++i )
	{
		float inX = topLeftX + ( ( maxLineWidth - lines[i].width ) / 2 );
		float inY = topLeftY + ( textHeight * i );

		float x, y;
		draw::Draw::get().convertScreenToWorldCoorinatesB( inX, inY, x, y );
		
		draw::ScopedColour scopedColour( draw::colour::kLightBlue );
		draw::Draw::get().text( lines[i].text.c_str(),
			x, y, lines[i].width, textHeight );
	}

	return true;
}