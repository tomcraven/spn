#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include "component/ComponentEntity.h"
#include "component/Clickable.h"
#include "component/Dimensions.h"
#include "component/Texture.h"
#include "component/Position.h"
#include "component/RenderTexture.h"

namespace game
{
	class Button : public component::ComponentEntity
	{
	public:
		Button();

		class Consumer
		{
		public:
			virtual bool onButtonConsumerClick( uint32_t id ) = 0;
		};

		void setConsumer( Consumer* inConsumer );
		bool onClickableConsumerClick();
		const uint32_t getId();
		virtual bool render();

	private:
		uint32_t id;
		Consumer* consumer;

		component::Clickable c;
		component::Position p;
		component::Dimensions d;
		component::Texture t;
		component::RenderTexture r;
	};
}

#endif