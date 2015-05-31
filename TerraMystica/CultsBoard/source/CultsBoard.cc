#include "CultsBoard.hh"

CultsBoard::CultsBoard()
{
}

CultsBoard::~CultsBoard()
{
}

unsigned int CultsBoard::increaseCultValue(const Factions faction, const Cults cult, unsigned int value)
{
    return values[cult].increaseCultValue(faction, value);
}

unsigned int CultsBoard::getCultValue(const Factions faction, const Cults cult)
{
    return values[cult].getCultValue(faction);
}
