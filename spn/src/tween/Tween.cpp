#include "tween/Tween.h"
#include "core/Algorithm.h"

namespace
{
	void clampFunction_fromLessThanTo( float from, float to, float& value )
	{
		value = core::algorithm::clamp( from, to, value );
	}

	void clampFunction_toLessThanFrom( float from, float to, float& value )
	{
		value = core::algorithm::clamp( to, from, value );
	}

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

		if ( from < to )
		{
			clampFunction = &clampFunction_fromLessThanTo;
		}
		else
		{
			clampFunction = &clampFunction_toLessThanFrom;
		}
		
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
		return timeTaken >= durationSeconds;
	}

	void Tween::reset()
	{ 
		tweenValue = 0;
		from = 0.0f;
		to = 0.0f;
		timeTaken = 0.0f;
		clampFunction = &clampFunction_fromLessThanTo;
		setterFunction = &setterFunction_null;
		delaySeconds = 0.0f;
		updateFunction = &Tween::updateTween;
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
		( *clampFunction )( from, to, value );
		( *setterFunction )( tweenValue, value );

		return !hasFinished();
	}
}