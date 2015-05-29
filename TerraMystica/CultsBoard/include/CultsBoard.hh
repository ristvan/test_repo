#pragma once

#include "Cults.hh"
#include "Factions.hh"

class CultsBoard
{
public:
    CultsBoard();
    ~CultsBoard();
    unsigned int increaseCultValue(const Factions faction, const Cults cult, const unsigned int num);
    unsigned int getCultValue(const Factions faction, const Cults cult);
private:
    unsigned int values[4][5];
};
