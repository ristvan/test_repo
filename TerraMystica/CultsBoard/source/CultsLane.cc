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
    FactionData(IPowerUser *powerUser, Factions faction);
    unsigned int getNumberOfKeys() const;
    void addPower(const unsigned int power);
    Factions getFaction() const { return faction; }
    unsigned int cultsValue;
private:
    IPowerUser *powerUser;
    Factions faction;
};

CultsLane::FactionData::FactionData(IPowerUser *powerUser, Factions faction)
    : cultsValue(MIN_CULT_LEVEL), powerUser(powerUser), faction(faction)
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
        factionData.insert(std::make_pair(faction, new FactionData(powerUser, faction))); 
        successfulnessOfAddingFaction = true;
    }
    return successfulnessOfAddingFaction;
}

unsigned int CultsLane::calculateReachingMaxLevel(CultsLane::FactionData &factionData,
                                                  unsigned int fromCultValue,
                                                  unsigned int toCultValue)
{
    if (toCultValue > MAX_CULT_LEVEL - 1)
    {
        // do no let in when already occupied or there is no enough keys.
        int usedKeyNumber = keyCounter.getNumberOfUsedKeys(factionData.getFaction());
        if (lastSpaceOfTrack == eNumberOfFactions && factionData.getNumberOfKeys() > usedKeyNumber)
        {
            toCultValue = MAX_CULT_LEVEL;
            keyCounter.useKey(factionData.getFaction());
            lastSpaceOfTrack = factionData.getFaction();
        }
        else
        {
            toCultValue = (fromCultValue == MAX_CULT_LEVEL) ? fromCultValue : MAX_CULT_LEVEL - 1;
        }
    }
    return toCultValue;
}

void CultsLane::initFaction(const Factions faction, const unsigned int cultValue)
{
    unsigned int actCultValue = cultValue;
    if (factionData.find(faction) == factionData.end())
    {
        return;
    }
    FactionData *localFactionData = factionData[faction];

    actCultValue = calculateReachingMaxLevel(*localFactionData, MIN_CULT_LEVEL, cultValue);

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

        newValue = calculateReachingMaxLevel(*localFactionData, previousValue, newValue);

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
