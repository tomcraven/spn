#include "core/Assert.h"
#include "draw/Draw.h"
#include "draw/TexturePool.h"
#include "input/Input.h"

#include "MainRoom.h"
#include "MenuRoom.h"

bool initGoAndShudownRoom( game::Room& room )
{
	CHECK( room.init() );
	CHECK( room.go() );
	CHECK( room.shutdown() );
	return true;
}

bool initialiseSingletons()
{
	CHECK( draw::Draw::get().init() );
	CHECK( input::Input::get().init() );
	return true;
}

bool shutdownSingletons()
{
	CHECK( input::Input::get().shutdown() );
	CHECK( draw::TexturePool::get().shutdown() );
	CHECK( draw::Draw::get().shutdown() );
	return true;
}

int main()
{
	CHECK_AND_RETURN( initialiseSingletons(), 1 );
	
	while ( !input::Input::userHasRequestedToExit() )
	{
		MenuRoom menuRoom;
		CHECK_AND_RETURN( initGoAndShudownRoom( menuRoom ), 1 );

		MenuRoom::MenuSelection menuSelection = menuRoom.getMenuSelection();
		switch( menuSelection )
		{
		case MenuRoom::kPlay:
			{
				MainRoom mainRoom;
				CHECK_AND_RETURN( initGoAndShudownRoom( mainRoom ), 1 );
			}
			break;
		case MenuRoom::kExit:
			input::Input::simulateUserRequestToExit();
			break;
		default:
			break;
		}
	}

	CHECK_AND_RETURN( shutdownSingletons(), 1 );

    return 0;
}