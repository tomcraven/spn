#ifndef TWEEN_ITWEEN_H
#define TWEEN_ITWEEN_H

#include "core/List.h"

namespace tween
{
	class ITween : public core::ListNode
	{
	public:
		virtual bool hasFinished() = 0;
	};
}

#endif