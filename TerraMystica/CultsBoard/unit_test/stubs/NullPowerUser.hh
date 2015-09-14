#pragma once

#include "PowerUser.hh"

class NullPowerUser : public PowerUser
{
public:
    virtual void addPower(const unsigned int) {}
    virtual unsigned int getNumberOfKeys() const { return 0; }
};
