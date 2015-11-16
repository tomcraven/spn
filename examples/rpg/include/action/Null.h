#ifndef ACTION_NULL_H
#define ACTION_NULL_H

#include "action/IAction.h"

namespace action
{
	class Null : public IAction
	{
	public:
		virtual bool update();
	};
}

#endif