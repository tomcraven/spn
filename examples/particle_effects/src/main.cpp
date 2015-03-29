#include "core/Assert.h"
#include "draw/Draw.h"
#include "draw/TexturePool.h"
#include "input/Input.h"
#include "tween/TweenFactory.h"
#include "game/Room.h"
#include "MainRoom.h"

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
	VALIDATE( tween::TweenFactory::get().init( 3000 ) );
	return true;
}

bool shutdownSingletons()
{
	VALIDATE( input::Input::get().shutdown() );
	VALIDATE( draw::TexturePool::get().shutdown() );
	VALIDATE( tween::TweenFactory::get().shutdown() );
	VALIDATE( draw::Draw::get().shutdown() );
	return true;
}

int main()
{
	VALIDATE_AND_RETURN( initialiseSingletons(), 1 );

	while ( !input::Input::userHasRequestedToExit() )
	{
		MainRoom mainRoom;
		initGoAndShudownRoom( mainRoom );
	}

	VALIDATE_AND_RETURN( shutdownSingletons(), 1 );

    return 0;
}