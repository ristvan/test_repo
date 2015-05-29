#include "CultsBoard.hh"

CultsBoard::CultsBoard()
{
    for (int cult = eFire; cult <= eAir; ++cult)
        for(int index = 0; index < 5; ++index)
        {
            values[cult][index] = 0;
        }
}

CultsBoard::~CultsBoard()
{
}

unsigned int CultsBoard::increaseCultValue(const Factions faction, const Cults cult, unsigned int value)
{
    values[cult][faction] += value;
    return value;
}

unsigned int CultsBoard::getCultValue(const Factions faction, const Cults cult)
{
    return values[cult][faction];
}
