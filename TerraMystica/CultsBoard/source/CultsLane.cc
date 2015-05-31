#include "CultsLane.hh"

CultsLane::CultsLane()
{
}

unsigned int CultsLane::increaseCultValue(const Factions faction, const unsigned int value)
{
    cultsValue[faction] += value;
    return value;
}

unsigned int CultsLane::getCultValue(const Factions faction) const
{
    return cultsValue.at(faction);
}
