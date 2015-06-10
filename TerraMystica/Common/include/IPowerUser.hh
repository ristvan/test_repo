#pragma once

class IPowerUser
{
public:
    virtual void addPower(const unsigned int power) = 0;
    virtual unsigned int getNumberOfKeys() const = 0;
};
