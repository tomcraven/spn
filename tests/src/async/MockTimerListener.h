#include <gmock/gmock.h>
#include "async/Timer.h"

class MockTimerListener : public async::Timer::Listener
{
public:
    MOCK_METHOD1( onTimerExpired, bool( uint32_t ) );
};