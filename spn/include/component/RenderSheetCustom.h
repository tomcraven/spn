#ifndef COMPONENT_RENDERSHEETCUSTOM_H
#define COMPONENT_RENDERSHEETCUSTOM_H

#include "component/IComponent.h"
#include "component/RenderSheet.h"

namespace component
{
	class RenderSheetCustom : public RenderSheet
	{
	public: // RenderSheet
		virtual bool shouldIncrementFrame( ComponentEntity* entity );
	};
}

#endif