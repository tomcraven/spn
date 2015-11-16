#ifndef COMPONENT_ANGULARVELOCITY_H
#define COMPONENT_ANGULARVELOCITY_H

#include "component/IComponent.h"
#include "core/Types.h"

namespace component
{
	class Rotation;

	class AngularVelocity : public IComponent
	{
	public:
		AngularVelocity();
		AngularVelocity( float v );
		
		void set( const AngularVelocity& other );
		void set( float velocity );

		float v;

	public: // IComponent
		virtual bool initComponent( ComponentEntity* entity );
		virtual bool update( ComponentEntity* entity, float timeStep );
		virtual uint32_t getType();

	private:
		Rotation* r;
	};
} 

#endif