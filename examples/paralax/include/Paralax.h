#ifndef PARALAX_H
#define PARALAX_H

#include "ParalaxPane.h"

class Paralax
{
public:
	virtual bool init( ParalaxPane::Config** paralaxPanes );
	virtual bool shutdown();
	virtual bool update( float timeStepSeconds );
	virtual bool render();

private:
	ParalaxPane* paralaxPanes;
	uint32_t numPanes;
};

#endif