#include "Paralax.h"
#include "core/Assert.h"
#include "draw/Draw.h"
#include "draw/Colour.h"
#include "tween/TweenFactory.h"

using namespace tween;

namespace
{
	uint32_t getNumConfigs( ParalaxPane::Config** configs )
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

bool Paralax::init( ParalaxPane::Config** config )
{

	VALIDATE( paralaxPanes );

	numPanes = getNumConfigs( config );
	paralaxPanes = new ParalaxPane[ numPanes ];

	for ( uint32_t i = 0; i < numPanes; ++i )
	{
		VALIDATE( paralaxPanes[i].init( *( config[i] ) ) );
	}

	return true;
}

bool Paralax::shutdown()
{
	delete[] paralaxPanes;
	return true;
}

bool Paralax::update( float timeStepSeconds )
{
	for ( uint32_t i = 0; i < numPanes; ++i )
	{
		VALIDATE( paralaxPanes[i].update( timeStepSeconds ) );
	}

	return true;
}

bool Paralax::render()
{
	for ( uint32_t i = 0; i < numPanes; ++i )
	{
		VALIDATE( paralaxPanes[i].render() );
	}

	return true;
}