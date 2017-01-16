#ifndef COMPONENT_MOCKICOMPONENT_H
#define COMPONENT_MOCKICOMPONENT_H

#include <gmock/gmock.h>
#include "component/IComponent.h"

namespace component
{
  class MockIComponent : public component::IComponent
  {
  public:
    MOCK_METHOD0( getType, uint32_t() );
    MOCK_METHOD1( init, bool( ComponentEntity* ) );
    MOCK_METHOD1( shutdown, bool( ComponentEntity* ) );
    MOCK_METHOD2( update, bool( ComponentEntity*, float ) );
  };
}

#endif