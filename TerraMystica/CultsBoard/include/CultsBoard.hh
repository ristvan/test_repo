#pragma once

#include "Cults.hh"
#include "Factions.hh"

class PowerUser;

class CultsBoard
{
public:
    virtual ~CultsBoard() {}
    virtual bool addFaction(const Factions faction,
                    PowerUser &powerUser,
                    const unsigned int fire,
                    const unsigned int water,
                    const unsigned int earth,
                    const unsigned int air) = 0;

    virtual unsigned int increaseCultValue(const Factions faction, const Cults cult, const unsigned int num) = 0;
    virtual unsigned int getCultValue(const Factions faction, const Cults cult) = 0;
    virtual unsigned int sendPriestToMaxSteps(const Factions faction, const Cults cult) = 0;
    virtual unsigned int sendPriestToOneStep(const Factions faction, const Cults cult) = 0;
};

//CultsBoard::~CultsBoard() {}
