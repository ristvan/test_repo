#pragma once

#include "Factions.hh"
#include <map>

class CultsLane
{
public:
    CultsLane();
    unsigned int increaseCultValue(const Factions faction, const unsigned int value);
    unsigned int getCultValue(const Factions faction) const;
private:
    std::map<Factions, unsigned int> cultsValue;
};
