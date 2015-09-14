#pragma once

#include "Factions.hh"
#include <map>

// forward declarations
class PowerUser;
class KeyCounter;

class CultsLane
{
public:
    CultsLane(KeyCounter &keyCounter);
    ~CultsLane();
    bool addFaction(const Factions faction, PowerUser &powerUser);
    void initFaction(const Factions faction, const unsigned int cultValue);
    unsigned int increaseCultValue(const Factions faction, const unsigned int value);
    unsigned int getCultValue(const Factions faction) const;
    unsigned int sendPriestToMaxSteps(const Factions faction);
private:
    class FactionData;

    unsigned int calculateReachingMaxLevel(FactionData &, unsigned int, unsigned int);
    std::map<Factions, FactionData*> factionData;
    KeyCounter& keyCounter;
    Factions lastSpaceOfTrack;
    unsigned int numberOfSentPriests;
};
