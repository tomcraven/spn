#ifndef TWEEN_TWEEN_H
#define TWEEN_TWEEN_H

#include "tween/ITween.h"
#include "core/Assert.h"
#include "tween/TweenParseTypes.h"

namespace tween
{
	class Tween : public ITween
	{
	public:
		Tween();
	
		bool init( int* inTweenValue );
		bool init( float* inTweenValue );
		void finalise();

	public:
		bool update( float timeStepSeconds );
		bool hasFinished();
	
	public:
		typedef float ( *TweenFunction )( float, float, float, float );
		TweenFunction tweenFunction;
		float from, to;
		float valueRange;
		float durationSeconds;
		float timeTaken;
		float delaySeconds;
		
		bool shouldRepeat;
		tween::RepeatType repeatType;

	private:
		void reset();

		bool ( Tween::*updateFunction )( float timeStepSeconds );
		bool updateDelay( float timeStepSeconds );
		bool updateTween( float timeStepSeconds );

		void ( *setterFunction )( void* valueToSet, float value );

		void updateValueRange();
		bool hasFinishedTime();
	
		void* tweenValue;
	};
}

#endif