#include <gtest/gtest.h>
#include "component/Position.h"

TEST( Position, ShouldConstruct )
{
    component::Position p;
}

TEST( Position, ShouldConstructWithCoordinates )
{
    float inputX = 23.0f;
    float inputY = 42.0f;
    component::Position p( inputX, inputY );
    ASSERT_FLOAT_EQ( inputX, p.x );
    ASSERT_FLOAT_EQ( inputY, p.y );
}

TEST(Position, ShouldSet )
{
    component::Position p;
    ASSERT_FLOAT_EQ( 0.0f, p.x );
    ASSERT_FLOAT_EQ( 0.0f, p.y );

    float inputX = 23.0f;
    float inputY = 42.0f;
    p.set( inputX, inputY );
    ASSERT_FLOAT_EQ( inputX, p.x );
    ASSERT_FLOAT_EQ( inputY, p.y );
}

TEST(Position, ShouldSetFromAnotherPositionObject )
{
    component::Position p1( 23.0f, 42.0f );
    component::Position p2( 123.0f, 321.0f );

    p1.set( p2 );
    ASSERT_FLOAT_EQ( p1.x, p2.x );
    ASSERT_FLOAT_EQ( p1.y, p2.y );
}