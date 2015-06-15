#include "CultsLane.hh"
#include "IPowerUser.hh"
#include "KeyCounter.hh"

const unsigned int MIN_CULT_LEVEL = 0;
const unsigned int MAX_CULT_LEVEL = 10;
                                                         /* 0  1  2  3  4  5  6  7  8  9 10 */
const unsigned int powerGainOnTrack[MAX_CULT_LEVEL + 1] = { 0, 0, 0, 1, 1, 3, 3, 5, 5, 5, 8 };

class CultsLane::FactionData
{
public:
    FactionData(IPowerUser *powerUser);
    unsigned int getNumberOfKeys() const;
    void addPower(const unsigned int power);
    unsigned int cultsValue;
private:
    IPowerUser *powerUser;
};

CultsLane::FactionData::FactionData(IPowerUser *powerUser)
    : powerUser(powerUser), cultsValue(MIN_CULT_LEVEL)
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
CultsLane::CultsLane(KeyCounter& keyCounter) :  keyCounter(keyCounter), lastSpaceOfTrack(eNumberOfFactions)
{
}

CultsLane::~CultsLane()
{
    for (auto localFactionData : factionData)
    {
        delete localFactionData.second;
    }
}

bool CultsLane::addFaction(const Factions faction, IPowerUser *powerUser)
{
    bool successfulnessOfAddingFaction = false;
    bool canFactionBeAdded = factionData.find(faction) == factionData.end();
    if (canFactionBeAdded)
    {
        factionData.insert(std::make_pair(faction, new FactionData(powerUser))); 
        successfulnessOfAddingFaction = true;
    }
    return successfulnessOfAddingFaction;
}

void CultsLane::initFaction(const Factions faction, const unsigned int cultValue)
{
    unsigned int actCultValue = cultValue;
    if (factionData.find(faction) == factionData.end())
    {
        return;
    }
    FactionData *localFactionData = factionData[faction];

    if (actCultValue > MAX_CULT_LEVEL - 1)
    {
        const unsigned int numberOfKeys = localFactionData->getNumberOfKeys();
        int usedKeyNumber = keyCounter.getNumberOfUsedKeys(faction);
        if (lastSpaceOfTrack == eNumberOfFactions && numberOfKeys > usedKeyNumber)
        {
            actCultValue = MAX_CULT_LEVEL;
            keyCounter.useKey(faction);
            lastSpaceOfTrack = faction;
        }
        else
        {
            actCultValue = MAX_CULT_LEVEL - 1;
        }
    }
    localFactionData->cultsValue = actCultValue;
}


unsigned int CultsLane::increaseCultValue(const Factions faction, const unsigned int value)
{
    unsigned int modificationValue = MIN_CULT_LEVEL;
    if (factionData.find(faction) != factionData.end())
    {
        FactionData *localFactionData = factionData[faction];
        modificationValue = value;

        const unsigned int previousValue = localFactionData->cultsValue;
        unsigned int newValue = previousValue + modificationValue;
        if (newValue > MAX_CULT_LEVEL - 1)
        {
            // do no let in when already occupied or there is no enough keys.
            int usedKeyNumber = keyCounter.getNumberOfUsedKeys(faction);
            if (lastSpaceOfTrack == eNumberOfFactions && localFactionData->getNumberOfKeys() > usedKeyNumber)
            {
                newValue = MAX_CULT_LEVEL;
                keyCounter.useKey(faction);
                lastSpaceOfTrack = faction;
            }
            else
            {
                newValue = (previousValue == MAX_CULT_LEVEL) ? previousValue : MAX_CULT_LEVEL - 1;
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
    unsigned int cultValue = MIN_CULT_LEVEL;
    if (factionData.find(faction) != factionData.end())
    {
        cultValue = factionData.at(faction)->cultsValue;
    }
    return cultValue;
}
