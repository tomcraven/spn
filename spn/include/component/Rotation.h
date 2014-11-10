#ifndef COMPONENT_ROTATION_H
#define COMPONENT_ROTATION_H

#include "component/IComponent.h"

namespace component
{
	class Rotation : public IComponent
	{
	public:
		Rotation();
		void set( float r );

		float r;

	public: // Component
		virtual uint32_t getType();
	};
}

#endif