#include "CultsLane.hh"
#include "IPowerUser.hh"

const unsigned int powerGainOnTrack[11] = {0,0,0,1,1,3,3,5,5,5,8};

class CultsLane::FactionData
{
public:
    FactionData(IPowerUser *powerUser, unsigned int cultsValue);
    IPowerUser *powerUser;
    unsigned int cultsValue;
};

CultsLane::FactionData::FactionData(IPowerUser *powerUser, unsigned int cultsValue)
    : powerUser(powerUser), cultsValue(cultsValue)
{
}

CultsLane::~CultsLane()
{
    for (auto localFactionData : factionData)
    {
        delete localFactionData.second;
    }
}

bool CultsLane::addFaction(const Factions faction,
                           IPowerUser *powerUser,
                           const unsigned int cultValue)
{
    bool successfulnessOfAddingFaction = false;
    bool canFactionBeAdded = factionData.find(faction) == factionData.end();
    if (canFactionBeAdded)
    {
        factionData.insert(std::make_pair(faction, new FactionData(powerUser, cultValue))); 
        successfulnessOfAddingFaction = true;
    }
    return successfulnessOfAddingFaction;
}


unsigned int CultsLane::increaseCultValue(const Factions faction, const unsigned int value)
{
    unsigned int modificationValue = 0;
    if (factionData.find(faction) != factionData.end())
    {
        FactionData *localFactionData = factionData[faction];
        modificationValue = value;

        const unsigned int previousValue = localFactionData->cultsValue;
        const unsigned int newValue = previousValue + modificationValue;
        const unsigned int realPowerGain = powerGainOnTrack[newValue] - powerGainOnTrack[previousValue];

        localFactionData->cultsValue = newValue;
        if (realPowerGain > 0 && localFactionData->powerUser)
        {
            localFactionData->powerUser->addPower(realPowerGain);
        }
    }
    return modificationValue;
}

unsigned int CultsLane::getCultValue(const Factions faction) const
{
    unsigned int cultValue = 0;
    if (factionData.find(faction) != factionData.end())
    {
        cultValue = factionData.at(faction)->cultsValue;
    }
    return cultValue;
}
