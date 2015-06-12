#include "KeyCounter.hh"

//KeyCounter::KeyCounter() {}

//KeyCounter::~KeyCounter() {}
void KeyCounter::addFaction(Factions faction)
{
    usedKeys[faction] = 0;
}

void KeyCounter::useKey(Factions faction)
{
    usedKeys[faction]++;
}

unsigned int KeyCounter::getNumberOfUsedKeys(Factions faction) const
{
    return usedKeys.at(faction);
}
