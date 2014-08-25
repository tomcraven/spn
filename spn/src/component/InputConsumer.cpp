#include "component/InputConsumer.h"
#include "component/ComponentEntity.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	bool InputConsumer::onAttach( ComponentEntity* entity )
	{
		input::Input::get().addConsumer( entity );
		return true;
	}
	
	uint32_t InputConsumer::getType()
	{
		return typeId;
	}
}