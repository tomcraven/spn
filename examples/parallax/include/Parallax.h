#ifndef PARALLAX_H
#define PARALLAX_H

#include "ParallaxPane.h"

class Parallax
{
public:
	virtual bool init( ParallaxPane::Config** paralaxPanes );
	virtual bool shutdown();
	virtual bool update( float timeStepSeconds );
	virtual bool render();

private:
	ParallaxPane* parallaxPanes;
	uint32_t numPanes;
};

#endif
