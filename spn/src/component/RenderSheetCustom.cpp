#include "component/RenderSheetCustom.h"
#include "component/ComponentEntity.h"

namespace component
{
	bool RenderSheetCustom::shouldIncrementFrame( ComponentEntity* entity )
	{
		return entity->shouldIncrementFrame();
	}
}