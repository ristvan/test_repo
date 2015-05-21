#pragma once

#include "Cults.hh"

class CultsBoard
{
public:
    CultsBoard();
    ~CultsBoard();
    unsigned int increaseCultValue(const Cults cult, const unsigned int num);
    unsigned int getCultValue(const Cults cult);
private:
    unsigned int values[4];
};
