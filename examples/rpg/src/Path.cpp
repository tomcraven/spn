#include "Path.h"
#include "core/Assert.h"

Path::Path() : numNodes( 0u )
{
}

bool Path::add( int32_t x, int32_t y )
{
	VALIDATE( numNodes < kMaxNumPathNodes - 1 );

	Node& node = nodes[ numNodes++ ];

	node.x = x;
	node.y = y;

	return true;
}

bool Path::peek( int32_t& x, int32_t& y )
{
	CHECK( numNodes > 0 );

	x = nodes[ numNodes - 1 ].x;
	y = nodes[ numNodes - 1 ].y;

	return true;
}

bool Path::pop()
{
	CHECK( numNodes > 0 );
	--numNodes;
	return true;
}

bool Path::clear()
{
	numNodes = 0;
	return true;
}

uint32_t Path::size()
{
	return numNodes;
}