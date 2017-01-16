#include <gtest/gtest.h>
#include "component/ComponentEntity.h"
#include "component/MockIComponent.h"

namespace
{
  class ComponentEntity : public testing::Test
  {
  protected:
    component::ComponentEntity entity;
  };
}

TEST_F( ComponentEntity, ShouldConstruct )
{
  // tested in fixture setup
}

TEST_F( ComponentEntity, ShouldAttachComponent )
{
  component::MockIComponent mockComponent;
  ASSERT_TRUE( entity.attach( &mockComponent ) );
}

TEST_F( ComponentEntity, ShouldGetComponent )
{
  component::MockIComponent mockComponent;
  EXPECT_CALL( &mockComponent, getType ).Once(Return(3));
}