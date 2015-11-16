#ifndef COMPONENT_VELOCITY_H
#define COMPONENT_VELOCITY_H

#include "component/IComponent.h"
#include "core/Types.h"

namespace component
{
	class Position;
	class Speed;

	class Velocity : public IComponent
	{
	public:
		Velocity();
		Velocity( float x, float y );
		
		void set( float x, float y );
		void set( const Velocity& other );

		void unit();
		void multiply( float val );

	public: // IComponent
		virtual bool initComponent( ComponentEntity* entity );
		virtual bool update( ComponentEntity* entity, float timeStep );
		virtual uint32_t getType();

		float x, y;

	private:
		Position* p;
		Speed* s;
	};
} 

#endif