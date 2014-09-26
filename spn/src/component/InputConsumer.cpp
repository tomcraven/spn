#include "component/InputConsumer.h"
#include "component/ComponentEntity.h"
#include "core/Assert.h"

namespace
{
	uint32_t typeId = component::IComponent::generateTypeId();
}

namespace component
{
	bool InputConsumer::init( ComponentEntity* entity )
	{
		CHECK( input::Input::get().addConsumer( entity ) );
		return true;
	}

	uint32_t InputConsumer::getType()
	{
		return typeId;
	}
}