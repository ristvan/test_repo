#pragma once

#include "CultsBoard.hh"
#include "Cults.hh"
#include "Factions.hh"
#include "KeyCounter.hh"
#include <map>

class PowerUser;
class CultsLane;

class CultsBoardImpl : public CultsBoard
{
public:
    CultsBoardImpl();
    ~CultsBoardImpl();
    bool addFaction(const Factions faction,
                    PowerUser &powerUser,
                    const unsigned int fire,
                    const unsigned int water,
                    const unsigned int earth,
                    const unsigned int air);

    unsigned int increaseCultValue(const Factions faction, const Cults cult, const unsigned int num);
    unsigned int getCultValue(const Factions faction, const Cults cult);

    unsigned int sendPriestToMaxSteps(const Factions faction, const Cults cult);
    unsigned int sendPriestToOneStep(const Factions faction, const Cults cult);
private:
    std::map<Cults, CultsLane*> values;
    KeyCounter keyCounter;
};
