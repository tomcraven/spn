#include "FancyButton.h"
#include "core/Assert.h"
#include "tween/TweenFactory.h"
#include "draw/ScopedColour.h"
#include "draw/ColourConstants.h"
#include "core/Rand.h"
#include "math/Math.h"
#include "emitter/Emitter.h"
#include "emitter/policy/Position.h"
#include "emitter/policy/Velocity.h"
#include "emitter/policy/AngularVelocity.h"
#include "emitter/policy/Emission.h"
#include "emitter/policy/Life.h"
#include "emitter/policy/Scale.h"
#include "emitter/policy/Texture.h"
#include "emitter/policy/Initialise.h"

namespace
{
	namespace emitterpolicies
	{
		emitter::policy::position::Rect position;
		emitter::policy::velocity::Circular velocity( math::pi / 3.0f, ( math::pi / 3.0f ) + ( math::pi / 3.0f ), 10.0f, 30.0f );
		emitter::policy::texture::Path texturePath( "textures/blank_smoke.png" );
		emitter::policy::emission::Timed emission( 0.006f );
		emitter::policy::life::Random life( 2.0f, 4.0f );
		emitter::policy::scale::Random2 scale( 0.3f, 0.6f, 0.01f, 0.06f );
		emitter::policy::angularvelocity::Random angularVelocity( -4.2f, 4.2f );

		class CustomInitialise : public emitter::policy::Initialise
		{
		public: // policy::Initialise
			bool initParticle( emitter::Particle* p )
			{
				float timeToLive = p->getTimeToLive();

				float scaleDownAtXPercentOfLifeLeft = 0.75f;
				float fadeInForXPercentOfLife = 0.25f;

				float fadeOutForXPercentOfLife = 0.75f;

				using namespace tween;
				TweenFactory::get().create(
					&p->getComponent< component::Scale >()->scale,
					FROM_CURRENT,
					TO, 0.0f,
					TWEEN_TYPE, LINEAR,
					OVER, ( timeToLive * ( 1 - scaleDownAtXPercentOfLifeLeft ) ), SECONDS,
					DELAYED_BY, timeToLive * scaleDownAtXPercentOfLifeLeft, SECONDS,
					TWEEN_END );
	
				component::Colour* colour = p->getComponent< component::Colour >();
				TweenFactory::get().create(
					&colour->alpha,
					FROM, 0.0f,
					TO, 255.0f,
					TWEEN_TYPE, LINEAR,
					OVER, ( timeToLive * fadeInForXPercentOfLife ), SECONDS,
					CLAMP,
					TWEEN_END );

				TweenFactory::get().create(
					&colour->alpha,
					FROM, 255.0f,
					TO, 0.0f,
					TWEEN_TYPE, LINEAR,
					OVER, timeToLive * fadeOutForXPercentOfLife, SECONDS,
					DELAYED_BY, ( timeToLive * ( 1 - fadeOutForXPercentOfLife ) ), SECONDS,
					CLAMP,
					TWEEN_END );

				TweenFactory::get().create(
					&colour->green,
					FROM, 25.0f,
					TO, 255.0f,
					TWEEN_TYPE, LINEAR,
					OVER, timeToLive, SECONDS,
					CLAMP,
					TWEEN_END );

				return true;
			}
		};
		CustomInitialise customInitialise;
	}
}

bool FancyButton::init()
{
	VALIDATE( Button::init() );

	emitter.init( 3000 );

	emitterpolicies::position.set( p, d );

	emitter.setPositionPolicy( &emitterpolicies::position );
	emitter.setVelocityPolicy( &emitterpolicies::velocity );
	emitter.setTexturePolicy( &emitterpolicies::texturePath );
	emitter.setEmissionPolicy( &emitterpolicies::emission );
	emitter.setLifePolicy( &emitterpolicies::life );
	emitter.setScalePolicy( &emitterpolicies::scale );
	emitter.setInitialisePolicy( &emitterpolicies::customInitialise );
	emitter.setAngularVelocityPolicy( &emitterpolicies::angularVelocity );

	return true;
}

bool FancyButton::shutdown()
{
	VALIDATE( Button::shutdown() );
	VALIDATE( emitter.shutdown() );
	return true;
}

bool FancyButton::update( float timeStep )
{
	VALIDATE( Button::update( timeStep ) );
	VALIDATE( emitter.update( timeStep ) );

	return true;
}

bool FancyButton::render()
{
	VALIDATE( emitter.render() );
	VALIDATE( Button::render() );

	return true;
}