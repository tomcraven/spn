#include "input/Input.h"
#include "core/Assert.h"

#include <s3ePointer.h>

namespace
{
	void singleTouchCallback( s3ePointerEvent* event, void* userData )
	{
		if ( !userData )
		{
			return;
		}

		if ( event->m_Pressed )
		{
			input::Input* input = reinterpret_cast<input::Input*>( userData );
			input->onButtonPress( event->m_x, event->m_y );
		}
	}

	input::Input instance;
}

namespace input
{
	Input& Input::get()
	{
		return instance;
	}

	bool Input::init()
	{
		CHECK_S3E_RESULT( s3ePointerRegister( S3E_POINTER_BUTTON_EVENT, 
			( s3eCallback )singleTouchCallback, this ) );

		return true;
	}

	bool Input::shutdown()
	{
		CHECK_S3E_RESULT( s3ePointerUnRegister( S3E_POINTER_BUTTON_EVENT, 
			( s3eCallback )singleTouchCallback ) );

		std::vector<Consumer*> temp;
		inputConsumers.swap( temp );

		return true;
	}

	bool Input::addConsumer( Consumer* consumer )
	{
		inputConsumers.push_back( consumer );
		return true;
	}

	void Input::onButtonPress( uint32_t x, uint32_t y )
	{
		std::vector<Consumer*>::iterator iter;
		for ( iter = inputConsumers.begin(); iter != inputConsumers.end(); ++iter )
		{
			(*iter)->onInputConsumerButtonDown( x, y );
		}
	}
}