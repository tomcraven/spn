#ifndef INPUT_INPUT_H
#define INPUT_INPUT_H

#include "core/List.h"

namespace input
{
	class Input
	{
	public:
		static Input& get();
		static bool userHasRequestedToExit();
		static void simulateUserRequestToExit();

		bool init();
		bool shutdown();

		bool update();

		class Consumer : public core::ListNode
		{
		public:
			virtual bool onInputConsumerButtonDown( uint32_t x, uint32_t y ) = 0;
		};
		bool addConsumer( Consumer* consumer );
		bool removeConsumer( Consumer* consumer );

		void onButtonPress( uint32_t x, uint32_t y );

	private:
		core::List< Consumer* > inputConsumers;
	};
}

#endif