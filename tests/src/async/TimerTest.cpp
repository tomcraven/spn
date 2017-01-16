#include <gtest/gtest.h>
#include "async/Timer.h"
#include "async/MockTimerListener.h"

namespace
{
    class Timer : public testing::Test
    {
    protected:
        async::Timer timer;
    };
}

TEST_F( Timer, ShouldConstruct )
{
    // Tested in fixture setup
}

TEST_F( Timer, ShouldSetListener )
{  
    timer.setListener( 0 );

    MockTimerListener mockListener;
    timer.setListener( &mockListener );
}

TEST_F( Timer, ShouldUpdate )
{
    ASSERT_TRUE( timer.update( 10.0f ) );
}

TEST_F( Timer, ShouldUpdateWithTimeout )
{
    timer.setTimeout( 5.0f );
    ASSERT_TRUE( timer.update( 6.0f ) );
}

TEST_F( Timer, ShouldGetId )
{
    async::Timer timer2;
    async::Timer timer3;

    ASSERT_NE( timer.getId(), timer2.getId() );
    ASSERT_NE( timer.getId(), timer3.getId() );
    ASSERT_NE( timer2.getId(), timer3.getId() );
}

TEST_F( Timer, ShouldUpdateWithTimeoutAndListener )
{
    MockTimerListener mockListener;
    timer.setListener( &mockListener );
    const float timeout = 5.0f;
    timer.setTimeout( timeout );

    EXPECT_CALL( mockListener, onTimerExpired( timer.getId() ) ).Times( 1 );
    ASSERT_TRUE( timer.update( timeout ) );
    ASSERT_TRUE( timer.update( timeout ) );
    ASSERT_TRUE( timer.update( timeout ) );
}

TEST_F( Timer, ShouldRepeat )
{
    MockTimerListener mockListener;
    timer.setListener( &mockListener );
    const float timeout = 5.0f;
    timer.setTimeout( timeout );
    timer.setRepeat( true );

    EXPECT_CALL( mockListener, onTimerExpired( timer.getId() ) ).Times( 3 );
    ASSERT_TRUE( timer.update( timeout ) );
    ASSERT_TRUE( timer.update( timeout ) );
    ASSERT_TRUE( timer.update( timeout ) );
}