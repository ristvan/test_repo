#include "CultsLane.hh"
#include "IPowerUser.hh"

const unsigned int powerGainOnTrack[11] = {0,0,0,1,1,3,3,5,5,5,8};

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
        int previousValue = cultsValue[faction];
        cultsValue[faction] += modificationValue = value;
        const unsigned int realPowerGain = powerGainOnTrack[cultsValue[faction]] - powerGainOnTrack[previousValue];
        if (realPowerGain > 0 && powerUsers[faction])
        {
            powerUsers[faction]->addPower(realPowerGain);
        }
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
