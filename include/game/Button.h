#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include "component/ComponentEntity.h"

namespace game
{
	class Button : public component::ComponentEntity
	{
	public:
		explicit Button( uint32_t id );

		class Consumer
		{
		public:
			virtual bool onButtonConsumerClick( uint32_t id ) = 0;
		};

		void setConsumer( Consumer* inConsumer );
		bool onClickableConsumerClick();

	private:
		uint32_t id;
		Consumer* consumer;
	};
}

#endif