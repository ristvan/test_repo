#include "CultsBoard.hh"
#include "CultsLane.hh"
#include "Cults.hh"
#include "IPowerUser.hh"

CultsBoard::CultsBoard()
{
   values.insert(std::make_pair(eFire,  new CultsLane(&keyCounter)));
   values.insert(std::make_pair(eWater,  new CultsLane(&keyCounter)));
   values.insert(std::make_pair(eEarth,  new CultsLane(&keyCounter)));
   values.insert(std::make_pair(eAir,  new CultsLane(&keyCounter)));
}

CultsBoard::~CultsBoard()
{
    delete values[eFire];
    delete values[eWater];
    delete values[eEarth];
    delete values[eAir];
}

bool CultsBoard::addFaction(const Factions faction,
                            IPowerUser *powerUser,
                            const unsigned int fire,
                            const unsigned int water,
                            const unsigned int earth,
                            const unsigned int air)
{
    bool factionCanBeAdded = values[eFire]->addFaction(faction, powerUser, fire) &&
                             values[eWater]->addFaction(faction, powerUser, water) &&
                             values[eEarth]->addFaction(faction, powerUser, earth) &&
                             values[eAir]->addFaction(faction, powerUser, air);
    if (factionCanBeAdded)
    {
        keyCounter.addFaction(faction);
    }
    return factionCanBeAdded;
}

unsigned int CultsBoard::increaseCultValue(const Factions faction, const Cults cult, unsigned int value)
{
    return values[cult]->increaseCultValue(faction, value);
}

unsigned int CultsBoard::getCultValue(const Factions faction, const Cults cult)
{
    return values[cult]->getCultValue(faction);
}
