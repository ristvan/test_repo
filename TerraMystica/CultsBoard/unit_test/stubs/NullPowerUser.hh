#pragma once

#include "IPowerUser.hh"

class NullPowerUser : public IPowerUser
{
public:
    virtual void addPower(const unsigned int) {}
    virtual unsigned int getNumberOfKeys() const { return 0; }
};
