#ifndef INPUT_INPUT_H
#define INPUT_INPUT_H

#include <vector>

namespace input
{
	class Input
	{
	public:
		static Input& get();

		bool init();
		bool shutdown();

		class Consumer
		{
		public:
			virtual bool onInputConsumerButtonDown( uint32_t x, uint32_t y ) = 0;
		};
		bool addConsumer( Consumer* consumer );

		void onButtonPress( uint32_t x, uint32_t y );

	private:
		std::vector<Consumer*> inputConsumers;
	};
}

#endif