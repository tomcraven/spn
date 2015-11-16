#ifndef LEVEL_H
#define LEVEL_H

namespace component
{
	class Position;
}
class Path;

class Level
{
public:
	virtual bool createPathTo( 
		const component::Position& start, 
		const component::Position& end,
		Path& path ) = 0;
	virtual bool positionIsWalkable(
		const component::Position& pos ) = 0;
	virtual uint32_t getWidth() = 0;
	virtual uint32_t getHeight() = 0;
};

#endif