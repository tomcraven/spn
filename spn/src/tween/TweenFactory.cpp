#include "tween/TweenFactory.h"

namespace
{
	float null( float valueRange, float timeTaken, float duration, float start )
	{
		return 0.0f;
	}

	float linear( float valueRange, float timeTaken, float duration, float start )
	{
		return valueRange * ( timeTaken / duration ) + start;
	}

	float quadratic( float valueRange, float timeTaken, float duration, float start )
	{
		timeTaken /= ( duration / 2 );
		if ( timeTaken < 1 )
		{
			float halfValueRange = valueRange / 2.0f;
			float timeTakenSquared = timeTaken * timeTaken;
			return ( halfValueRange * timeTakenSquared ) + start;
		}
		else
		{
			--timeTaken;
			float halfValueRange = valueRange / 2.0f;
			return -halfValueRange * ( timeTaken * ( timeTaken - 2 ) -1 ) + start;
		}
	}

	float quadratic_in( float valueRange, float timeTaken, float duration, float start )
	{
		timeTaken /= duration;
		return valueRange * timeTaken * timeTaken + start;
	}
	
	float bounce_in( float valueRange, float timeTaken, float duration, float start )
	{
		return 0.0f;
	}

	float bounce_out( float valueRange, float timeTaken, float duration, float start )
	{
		return 0.0f;
	}
}

namespace tween
{
	TweenFactory& TweenFactory::get()
	{
		static TweenFactory tweenFactory;
		return tweenFactory;
	}

	bool TweenFactory::init( uint32_t tweenPoolSize )
	{
		VALIDATE( tweenPool.init( tweenPoolSize ) );
		return true;
	}

	bool TweenFactory::shutdown()
	{
		VALIDATE( removeAllTweens() );
		VALIDATE( tweenPool.shutdown() );
		return true;
	}

	bool TweenFactory::update( float timeStepSeconds )
	{
		TweenContainer::Iterator tweenIter = tweens.begin();
		for( ; tweenIter != tweens.end() ; )
		{
			if ( !( *tweenIter )->update( timeStepSeconds ) )
			{ 
				tweenPool.free( *tweenIter );
				tweenIter = tweens.erase( tweenIter );
			}
			else
			{
				++tweenIter;
			}
		}

		return true;
	}

	bool TweenFactory::removeAllTweens()
	{
		TweenContainer::Iterator tweenIter = tweens.begin();
		for( ; tweenIter != tweens.end() ; )
		{
			tweenPool.free( *tweenIter );
			tweenIter = tweens.erase( tweenIter );
		}
		
		return true;
	}

	Tween::TweenFunction TweenFactory::getTweenFunction( TweenType tweenType )
	{
		switch( tweenType )
		{
		case LINEAR:
			return &linear;
		case QUADRATIC:
			return &quadratic;
		case QUADRATIC_IN:
			return &quadratic_in;
		case BOUNCE_IN:
			return &bounce_in;
		case BOUNCE_OUT:
			return &bounce_out;
		default:
			break;
		}

		return &null;
	}
}