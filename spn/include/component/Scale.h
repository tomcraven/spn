#ifndef COMPONENT_SCALE_H
#define COMPONENT_SCALE_H

#include "component/IComponent.h"

namespace component
{
	class Scale : public IComponent
	{
	public:
		Scale( float scale = 1.0f );
		void set( float scale );

		float scale;

	public: // Component
		virtual uint32_t getType();
	};
}

#endif