#include "CultsLane.hh"

CultsLane::CultsLane()
{
}

bool CultsLane::addFaction(const Factions faction,
                           IPowerUser *powerUser,
                           const unsigned int cultValue)
{
    bool successfulnessOfAddingFaction = false;
    bool canFactionBeAdded = cultsValue.find(faction) == cultsValue.end();
    if (canFactionBeAdded)
    {
        cultsValue[faction] = cultValue;
        powerUsers[faction] = powerUser;
        successfulnessOfAddingFaction = true;
    }
    return successfulnessOfAddingFaction;
}


unsigned int CultsLane::increaseCultValue(const Factions faction, const unsigned int value)
{
    unsigned int modificationValue = 0;
    if (cultsValue.find(faction) != cultsValue.end())
    {
        cultsValue[faction] += modificationValue = value;
    }
    return modificationValue;
}

unsigned int CultsLane::getCultValue(const Factions faction) const
{
    unsigned int cultValue = 0;
    if (cultsValue.find(faction) != cultsValue.end())
    {
        cultValue = cultsValue.at(faction);
    }
    return cultValue;
}
