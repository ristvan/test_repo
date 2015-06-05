#pragma once

#include "Factions.hh"
#include <map>

// forward declarations
class IPowerUser;

class CultsLane
{
public:
    ~CultsLane();
    bool addFaction(const Factions faction,
                    IPowerUser *powerUser,
                    const unsigned int cultValue);
    unsigned int increaseCultValue(const Factions faction, const unsigned int value);
    unsigned int getCultValue(const Factions faction) const;
private:
    class FactionData;
    std::map<Factions, FactionData*> factionData;
};
