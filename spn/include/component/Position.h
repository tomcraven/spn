#ifndef COMPONENT_POSITION_H
#define COMPONENT_POSITION_H

#include "component/IComponent.h"

namespace component
{
	class Position : public IComponent
	{
	public:
		Position();
		Position( float x, float y );
		void set( float x, float y );

		float x, y;

	public: // Component
		virtual uint32_t getType();
	};
}

#endif