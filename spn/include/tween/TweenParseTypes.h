#ifndef TWEEN_TWEENPARSETYPES_H
#define TWEEN_TWEENPARSETYPES_H

namespace tween
{
	enum CreateParseState
	{
		UNKNOWN = -1,
		FROM,
		FROM_CURRENT,
		TO,
		TWEEN_TYPE,
		OVER,
		DELAYED_BY,
		REPEAT,
		REPEAT_ONCE,
		END
	};

	enum DurationUnits
	{
		SECONDS,
		MILLISECONDS,
	};

	enum RepeatType
	{
		MIRROR,
		RESTART
	};

	enum TweenType
	{
		LINEAR,
		QUADRATIC,
		QUADRATIC_IN,
		BOUNCE_IN,
		BOUNCE_OUT
	};
}

#endif