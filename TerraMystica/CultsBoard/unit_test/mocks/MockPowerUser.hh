#pragma once

#include "PowerUser.hh"
#include "gmock/gmock.h"

class MockPowerUser : public PowerUser {
 public:
  MOCK_METHOD1(addPower,
      void(const unsigned int power));
  MOCK_CONST_METHOD0(getNumberOfKeys,
      unsigned int());
};
