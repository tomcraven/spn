#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "core/Types.h"

namespace talk
{
	struct Line;
}

class TextBox
{
public:
	bool init( talk::Line* lines, uint32_t numLines );
	bool render();

private:
	talk::Line* lines;
	uint32_t numLines;
};

#endif