#pragma once

#include "Cults.hh"
#include "Factions.hh"
#include "CultsLane.hh"

class CultsBoard
{
public:
    CultsBoard();
    ~CultsBoard();
    unsigned int increaseCultValue(const Factions faction, const Cults cult, const unsigned int num);
    unsigned int getCultValue(const Factions faction, const Cults cult);
private:
    CultsLane values[4];
};
