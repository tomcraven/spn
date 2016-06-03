#include "Parallax.h"
#include "core/Assert.h"
#include "draw/Draw.h"
#include "draw/ColourConstants.h"
#include "tween/TweenFactory.h"

using namespace tween;

namespace
{
	uint32_t getNumConfigs( ParallaxPane::Config** configs )
	{
		uint32_t ret = 0;
		while( *configs )
		{
			++ret;
			++configs;
		}
		return ret;
	}
}

bool Parallax::init( ParallaxPane::Config** config )
{

	VALIDATE( parallaxPanes );

	numPanes = getNumConfigs( config );
	parallaxPanes = new ParallaxPane[ numPanes ];

	for ( uint32_t i = 0; i < numPanes; ++i )
	{
		VALIDATE( parallaxPanes[i].init( *( config[i] ) ) );
	}

	return true;
}

bool Parallax::shutdown()
{
	delete[] parallaxPanes;
	return true;
}

bool Parallax::update( float timeStepSeconds )
{
	for ( uint32_t i = 0; i < numPanes; ++i )
	{
		VALIDATE( parallaxPanes[i].update( timeStepSeconds ) );
	}

	return true;
}

bool Parallax::render()
{
	for ( uint32_t i = 0; i < numPanes; ++i )
	{
		VALIDATE( parallaxPanes[i].render() );
	}

	return true;
}
