#include "CultsLane.hh"
#include "IPowerUser.hh"
                                         /* 0  1  2  3  4  5  6  7  8  9 10 */
const unsigned int powerGainOnTrack[11] = { 0, 0, 0, 1, 1, 3, 3, 5, 5, 5, 8 };

class CultsLane::FactionData
{
public:
    FactionData(IPowerUser *powerUser, unsigned int cultsValue);
    unsigned int getNumberOfKeys() const;
    void addPower(const unsigned int power);
    unsigned int cultsValue;
private:
    IPowerUser *powerUser;
};

CultsLane::FactionData::FactionData(IPowerUser *powerUser, unsigned int cultsValue)
    : powerUser(powerUser), cultsValue(cultsValue)
{
}

unsigned int CultsLane::FactionData::getNumberOfKeys() const
{
   unsigned int numberOfKeys = 0;
   if (powerUser)
   {
       numberOfKeys = powerUser->getNumberOfKeys();
   }
   return numberOfKeys;
}

void CultsLane::FactionData::addPower(const unsigned int power)
{
   if (power > 0 && powerUser)
   {
       powerUser->addPower(power);
   }
}

// CultsLane implementation
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
        unsigned int newValue = previousValue + modificationValue;
        if (newValue > 9)
        {
            if (localFactionData->getNumberOfKeys() > 0)
            {
                newValue = 10;
            }
            else
            {
                newValue = 9;
            }
        }
        modificationValue = newValue - previousValue;
        const unsigned int realPowerGain = powerGainOnTrack[newValue] - powerGainOnTrack[previousValue];

        localFactionData->cultsValue = newValue;
        localFactionData->addPower(realPowerGain);
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
