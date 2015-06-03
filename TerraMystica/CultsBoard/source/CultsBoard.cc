#include "CultsBoard.hh"
#include "IPowerUser.hh"

CultsBoard::CultsBoard()
{
}

CultsBoard::~CultsBoard()
{
}
bool CultsBoard::addFaction(const Factions faction,
                            IPowerUser *powerUser,
                            const unsigned int fire,
                            const unsigned int water,
                            const unsigned int earth,
                            const unsigned int air)
{
    bool factionCanBeAdded = values[eFire].addFaction(faction, powerUser, fire) &&
                             values[eWater].addFaction(faction, powerUser, water) &&
                             values[eEarth].addFaction(faction, powerUser, earth) &&
                             values[eAir].addFaction(faction, powerUser, air);
    return factionCanBeAdded;
}

unsigned int CultsBoard::increaseCultValue(const Factions faction, const Cults cult, unsigned int value)
{
    return values[cult].increaseCultValue(faction, value);
}

unsigned int CultsBoard::getCultValue(const Factions faction, const Cults cult)
{
    return values[cult].getCultValue(faction);
}
