#include "input/Input.h"
#include "core/Assert.h"

#include <sdl.h>

namespace
{
	input::Input instance;
}

namespace input
{
	Input::Input() : userWantsToExit( false )
	{
	}

	Input& Input::get()
	{
		return instance;
	}

	bool Input::userHasRequestedToExit()
	{
		return instance.userWantsToExit;
	}

	void Input::simulateUserRequestToExit()
	{
		SDL_Event quitEvent;
		quitEvent.type = SDL_QUIT;

		SDL_PushEvent( &quitEvent );
	}

	bool Input::init()
	{
		return true;
	}

	bool Input::shutdown()
	{
		return true;
	}

	bool Input::update()
	{
		SDL_Event event;
		while( SDL_PollEvent( &event ) )
		{
			if ( event.type == SDL_QUIT )
			{
				userWantsToExit = true;
			}
		}

		return true;
	}

	bool Input::addConsumer( Consumer* consumer )
	{
		inputConsumers.push_back( consumer );
		return true;
	}

	bool Input::removeConsumer( Consumer* consumer )
	{
		core::List< Consumer* >::Iterator consumerIter;
		consumerIter = inputConsumers.find( consumer );

		//VALIDATE( consumerIter != inputConsumers.end() );
		//inputConsumers.erase( consumerIter );

		return true;
	}

	void Input::onButtonPress( uint32_t x, uint32_t y )
	{
		core::List< Consumer* >::Iterator iter;
		for ( iter = inputConsumers.begin(); iter != inputConsumers.end(); ++iter )
		{
			(*iter)->onInputConsumerButtonDown( x, y );
		}
	}
}