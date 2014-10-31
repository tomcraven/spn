#ifndef TWEEN_ITWEEN_H
#define TWEEN_ITWEEN_H

namespace tween
{
	class ITween
	{
	public:
		virtual bool hasFinished() = 0;
	};
}

#endif