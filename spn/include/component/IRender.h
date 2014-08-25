#ifndef COMPONENT_IRENDER_H
#define COMPONENT_IRENDER_H

namespace component
{
	class Position;

	class IRender
	{
	public:
		virtual bool render( const Position& p ) = 0;
	};
}

#endif