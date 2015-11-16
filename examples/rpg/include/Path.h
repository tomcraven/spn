#ifndef PATH_H
#define PATH_H

#include "core/Types.h"

namespace
{
	const uint32_t kMaxNumPathNodes = 32u;
}

class Path
{
public:
	Path();
	bool add( int32_t x, int32_t y );
	bool peek( int32_t& x, int32_t& y );
	bool pop();
	bool clear();
	uint32_t size();

private:
	uint32_t numNodes;
	
	struct Node
	{
		Node() : x( 0 ), y( 0 )
		{}

		int32_t x, y;
	};

	Node nodes[ kMaxNumPathNodes ];
};

#endif