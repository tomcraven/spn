#include <gtest/gtest.h>
#include "component/Velocity.h"

TEST( Velocity, ShouldConstruct )
{
    component::Velocity v;
}

TEST( Velocity, ShouldConstructWithCoordinates )
{
    float inputX = 23.0f;
    float inputY = 42.0f;
    component::Velocity v( inputX, inputY );
    ASSERT_FLOAT_EQ( inputX, v.x );
    ASSERT_FLOAT_EQ( inputY, v.y );
}

TEST(Velocity, ShouldSet )
{
    component::Velocity v;
    ASSERT_FLOAT_EQ( 0.0f, v.x );
    ASSERT_FLOAT_EQ( 0.0f, v.y );

    float inputX = 23.0f;
    float inputY = 42.0f;
    v.set( inputX, inputY );
    ASSERT_FLOAT_EQ( inputX, v.x );
    ASSERT_FLOAT_EQ( inputY, v.y );
}

TEST(Velocity, ShouldSetFromAnotherVelocityObject )
{
    component::Velocity v1( 23.0f, 42.0f );
    component::Velocity v2( 123.0f, 321.0f );

    v1.set( v2 );
    ASSERT_FLOAT_EQ( v1.x, v2.x );
    ASSERT_FLOAT_EQ( v1.y, v2.y );
}

TEST( Velocity, ShouldInit )
{
    // TODO after ive done the component entity tests
    ASSERT_TRUE( false );
}