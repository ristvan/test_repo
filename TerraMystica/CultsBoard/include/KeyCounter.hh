#pragma once
#include "Factions.hh"
#include <map>

class KeyCounter
{
public:
    void addFaction(Factions faction);
    void useKey(Factions faction);
    unsigned int getNumberOfUsedKeys(Factions faction) const;
private:
    typedef std::map<Factions, unsigned int> KeyUsage;
    KeyUsage usedKeys;
};
