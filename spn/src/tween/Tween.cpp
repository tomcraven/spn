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
	
	void clampFunction_low_high( float low, float high, float& value )
	{
		value = core::algorithm::min( high, core::algorithm::max( low, value ) );
	}

	void clampFunction_high_low( float high, float low, float& value )
	{
		value = core::algorithm::min( high, core::algorithm::max( low, value ) );
	}

	void clampFunction_null( float low, float high, float& value )
	{
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

	bool Tween::init( uint32_t* inTweenValue )
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
		
		if ( delaySeconds > 0.0f )
		{
			updateFunction = &Tween::updateDelay;
		}
		else
		{
			( *setterFunction )( tweenValue, from );
		}

		if ( shouldClamp )
		{
			if ( from < to )
			{
				clampFunction = &clampFunction_low_high;
			}
			else
			{
				clampFunction = &clampFunction_high_low;
			}
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
		clampFunction = &clampFunction_null;
		shouldClamp = false;
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