#ifndef ACTION_IACTION_H
#define ACTION_IACTION_H

namespace action
{
	class IAction
	{
	public:
		virtual ~IAction() {}
		virtual bool update() = 0;
	};
}

#endif