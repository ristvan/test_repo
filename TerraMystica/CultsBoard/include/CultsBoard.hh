#pragma once

#include "Cults.hh"
#include "Factions.hh"
#include "KeyCounter.hh"
#include <map>

class IPowerUser;
class CultsLane;

class CultsBoard
{
public:
    CultsBoard();
    ~CultsBoard();
    bool addFaction(const Factions faction,
                    IPowerUser &powerUser,
                    const unsigned int fire,
                    const unsigned int water,
                    const unsigned int earth,
                    const unsigned int air);

    unsigned int increaseCultValue(const Factions faction, const Cults cult, const unsigned int num);
    unsigned int getCultValue(const Factions faction, const Cults cult);
private:
    std::map<Cults, CultsLane*> values;
    KeyCounter keyCounter;
};
