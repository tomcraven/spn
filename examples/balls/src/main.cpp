#include "core/Assert.h"
#include "draw/Draw.h"
#include "draw/TexturePool.h"
#include "input/Input.h"

#include "MainRoom.h"
#include "MenuRoom.h"

bool initGoAndShudownRoom( game::Room& room )
{
	VALIDATE( room.init() );
	VALIDATE( room.go() );
	VALIDATE( room.shutdown() );
	return true;
}

bool initialiseSingletons()
{
	VALIDATE( draw::Draw::get().init() );
	VALIDATE( input::Input::get().init() );
	return true;
}

bool shutdownSingletons()
{
	VALIDATE( input::Input::get().shutdown() );
	VALIDATE( draw::TexturePool::get().shutdown() );
	VALIDATE( draw::Draw::get().shutdown() );
	return true;
}

int main()
{
	VALIDATE_AND_RETURN( initialiseSingletons(), 1 );
	
	while ( !input::Input::userHasRequestedToExit() )
	{
		MenuRoom menuRoom;
		VALIDATE_AND_RETURN( initGoAndShudownRoom( menuRoom ), 1 );

		MenuRoom::MenuSelection menuSelection = menuRoom.getMenuSelection();
		switch( menuSelection )
		{
		case MenuRoom::kPlay:
			{
				MainRoom mainRoom;
				VALIDATE_AND_RETURN( initGoAndShudownRoom( mainRoom ), 1 );
			}
			break;
		case MenuRoom::kExit:
			input::Input::simulateUserRequestToExit();
			break;
		default:
			break;
		}
	}

	VALIDATE_AND_RETURN( shutdownSingletons(), 1 );

    return 0;
}