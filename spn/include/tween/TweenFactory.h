#ifndef TWEEN_TWEENFACTORY_H
#define TWEEN_TWEENFACTORY_H

#include "core/AssetPool.h"
#include "core/Assert.h"
#include "tween/Tween.h"
#include "tween/TweenParseTypes.h"

#include <stdarg.h>

namespace tween
{
	class TweenFactory
	{
	public:
		static TweenFactory& get();
		bool init( uint32_t tweenPoolSize );
		bool shutdown();

		bool update( float timeStepSeconds );
		
		bool removeAllTweens();

		template < class T >
		ITween* create( T* a, ... )
		{
			Tween* newTween = tweenPool.alloc();
			VALIDATE_AND_RETURN( newTween, 0 );
			VALIDATE_AND_RETURN( newTween->init( a ), 0 );

			va_list tweenVaList;
			va_start( tweenVaList, a );

			float startingValue = 0.0f;
			bool hasStartingValue = false;

			CreateParseState parseState = UNKNOWN;
			while( parseState != TWEEN_END )
			{
				parseState = static_cast< CreateParseState >( va_arg( tweenVaList, int ) );
				switch( parseState )
				{
				case FROM:
					newTween->from = static_cast< float >( va_arg( tweenVaList, double ) );
					break;
				case FROM_CURRENT:
					newTween->from = static_cast< float >( *a );
					break;
				case TO:
					newTween->to = static_cast< float >( va_arg( tweenVaList, double ) );
					break;
				case OVER:
					{
						float duration = static_cast< float >( va_arg( tweenVaList, double ) );
						DurationUnits durationUnits = static_cast< DurationUnits >( va_arg( tweenVaList, int ) );
						switch( durationUnits )
						{
						case SECONDS:
							newTween->durationSeconds = duration;
							break;
						case MILLISECONDS:
							newTween->durationSeconds = ( duration / 1000.0f );
							break;
						default:
							break;
						}
					}
					break;
				case TWEEN_TYPE:
					{
						TweenType tweenType = static_cast< TweenType >( va_arg( tweenVaList, int ) );
						newTween->tweenFunction = getTweenFunction( tweenType );
					}
					break;
				case DELAYED_BY:
					{
						float duration = static_cast< float >( va_arg( tweenVaList, double ) );
						DurationUnits durationUnits = static_cast< DurationUnits >( va_arg( tweenVaList, int ) );
						switch( durationUnits )
						{
						case SECONDS:
							newTween->delaySeconds = duration;
							break;
						case MILLISECONDS:
							newTween->delaySeconds = ( duration / 1000.0f );
							break;
						default:
							break;
						}
					}
					break;
				case REPEAT:
					newTween->shouldRepeat = true;
					newTween->repeatType = static_cast< RepeatType >( va_arg( tweenVaList, int ) );
					break;
				case CLAMP:
					newTween->shouldClamp = true;
					break;
				case UNKNOWN:
				default:
					break;
				}
			}

			va_end( tweenVaList );
		
			tweens.push_back( newTween );

			newTween->finalise();
			return newTween;
		}

	private:
		Tween::TweenFunction getTweenFunction( TweenType tweenType );

		core::AssetPool< Tween > tweenPool;

		typedef core::List< Tween* >TweenContainer;
		TweenContainer tweens;
	};
}

#endif