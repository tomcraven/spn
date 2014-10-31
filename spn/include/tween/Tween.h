#ifndef TWEEN_TWEEN_H
#define TWEEN_TWEEN_H

#include "tween/ITween.h"
#include "core/Assert.h"

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

	private:
		void reset();

		bool ( Tween::*updateFunction )( float timeStepSeconds );
		bool updateDelay( float timeStepSeconds );
		bool updateTween( float timeStepSeconds );

		void ( *clampFunction )( float from, float to, float& value );
		void ( *setterFunction )( void* valueToSet, float value );

		void updateValueRange();
	
		void* tweenValue;
	};
}

#endif