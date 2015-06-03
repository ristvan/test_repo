#pragma once

#include "IPowerUser.hh"
#include "gmock/gmock.h"

class MockIPowerUser : public IPowerUser {
 public:
  MOCK_METHOD1(addPower,
      void(const unsigned int power));
};
