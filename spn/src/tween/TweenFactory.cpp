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
}

namespace tween
{
	TweenFactory& TweenFactory::get()
	{
		static TweenFactory tweenFactory;
		return tweenFactory;
	}

	bool TweenFactory::init()
	{
		VALIDATE( tweenPool.init( 10 ) );
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
		TweenContainer::iterator tweenIter = tweens.begin();
		for( ; tweenIter != tweens.end() ; )
		{
			if ( !( *tweenIter )->update( timeStepSeconds ) )
			{
				tweenPool.free( *tweenIter );
				tweens.erase( tweenIter );
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
		TweenContainer::iterator tweenIter = tweens.begin();
		for( ; tweenIter != tweens.end() ; )
		{
			tweenPool.free( *tweenIter );
			tweens.erase( tweenIter );
		}
		
		// Cannot use vector.clear as it leaves allocations that cause an assertion during Iw2DTerminate
		TweenContainer().swap( tweens );

		return true;
	}

	Tween::TweenFunction TweenFactory::getTweenFunction( CreateParseState parseState )
	{
		switch( parseState )
		{
		case LINEAR:
			return &linear;
		default:
			break;
		}

		return &null;
	}
}