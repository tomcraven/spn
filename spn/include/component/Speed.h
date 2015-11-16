#ifndef COMPONENT_SPEED_H
#define COMPONENT_SPEED_H

#include "component/IComponent.h"

namespace component
{
	class Speed : public IComponent
	{
	public:
		Speed();
		Speed( float s );

		void set( float val );

	public: // IComponent
		virtual uint32_t getType();

		float s;
	};
} 

#endif