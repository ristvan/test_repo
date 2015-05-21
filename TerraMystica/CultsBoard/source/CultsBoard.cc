#include "CultsBoard.hh"

CultsBoard::CultsBoard()
{
    values[eFire] = 0;
    values[eWater] = 0;
    values[eEarth] = 0;
    values[eAir] = 0;
}

CultsBoard::~CultsBoard()
{
}

unsigned int CultsBoard::increaseCultValue(Cults cult, unsigned int value)
{
    values[cult] += value;
    return value;
}

unsigned int CultsBoard::getCultValue(Cults cult)
{
    return values[cult];
}
