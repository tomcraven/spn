#include "tween/Tween.h"
#include "core/Algorithm.h"

namespace
{
	void setterFunction_null( void* valueToSet, float value )
	{
		*reinterpret_cast< int* >( valueToSet ) = 0;
	}
	
	void setterFunction_int( void* valueToSet, float value )
	{
		*reinterpret_cast< int* >( valueToSet ) = static_cast< int >( value );
	}

	void setterFunction_float( void* valueToSet, float value )
	{
		*reinterpret_cast< float* >( valueToSet ) = static_cast< float >( value );
	}
}

namespace tween
{
	Tween::Tween()
	{
		reset();
	}
	
	bool Tween::init( int* inTweenValue )
	{
		reset();
		VALIDATE( inTweenValue );
		tweenValue = inTweenValue;
		setterFunction = &setterFunction_int;
		return true;
	}

	bool Tween::init( float* inTweenValue )
	{
		reset();
		VALIDATE( inTweenValue );
		tweenValue = inTweenValue;
		setterFunction = &setterFunction_float;
		return true;
	}

	void Tween::finalise()
	{
		updateValueRange();
		
		( *setterFunction )( tweenValue, from );

		if ( delaySeconds > 0.0f )
		{
			updateFunction = &Tween::updateDelay;
		}
	}

	bool Tween::update( float timeStepSeconds )
	{
		CHECK( ( this->*updateFunction )( timeStepSeconds ) );
		return true;
	}

	bool Tween::hasFinished()
	{
		return ( !shouldRepeat ) && hasFinishedTime();
	}

	bool Tween::hasFinishedTime()
	{
		return ( timeTaken >= durationSeconds );
	}

	void Tween::reset()
	{ 
		tweenValue = 0;
		from = 0.0f;
		to = 0.0f;
		timeTaken = 0.0f;
		setterFunction = &setterFunction_null;
		delaySeconds = 0.0f;
		updateFunction = &Tween::updateTween;
		shouldRepeat = false;
	}
	
	void Tween::updateValueRange()
	{
		valueRange = to - from;
	}

	bool Tween::updateDelay( float timeStepSeconds )
	{
		delaySeconds -= timeStepSeconds;
		if ( delaySeconds <= 0.0f )
		{
			updateFunction = &Tween::updateTween;
		}

		return true;
	}

	bool Tween::updateTween( float timeStepSeconds )
	{
		timeTaken += timeStepSeconds;
		float value = ( *tweenFunction )( valueRange, timeTaken, durationSeconds, from );
		( *setterFunction )( tweenValue, value );

		if ( shouldRepeat && hasFinishedTime() )
		{
			switch( repeatType )
			{
			case MIRROR:
				core::algorithm::swap( from, to );
				// fall through
			case RESTART:
				timeTaken = 0.0f;
				finalise();
				break;
			default:
				break;
			}
		}

		return !hasFinished();
	}
}