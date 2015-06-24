#pragma once

#include "Cults.hh"
#include "Factions.hh"

class IPowerUser;

class ICultsBoard
{
public:
    virtual ~ICultsBoard() {}
    virtual bool addFaction(const Factions faction,
                    IPowerUser &powerUser,
                    const unsigned int fire,
                    const unsigned int water,
                    const unsigned int earth,
                    const unsigned int air) = 0;

    virtual unsigned int increaseCultValue(const Factions faction, const Cults cult, const unsigned int num) = 0;
    virtual unsigned int getCultValue(const Factions faction, const Cults cult) = 0;
    virtual unsigned int sendPriestToMaxSteps(const Factions faction, const Cults cult) = 0;
    virtual unsigned int sendPriestToOneStep(const Factions faction, const Cults cult) = 0;
};

//ICultsBoard::~ICultsBoard() {}
