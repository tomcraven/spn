#include "async/Thread.h"
#include "s3e.h"

namespace async
{
	void Thread::sleep( float seconds )
	{
        s3eDeviceYield( static_cast< int32_t >( seconds * 1000.0f ) );
	}
}