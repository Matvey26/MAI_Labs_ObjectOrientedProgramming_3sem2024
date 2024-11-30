#pragma once

#include "NPC.hpp"
#include <memory>

class Druid : public NPC {
public:
    Druid() : NPC("Druid") {}

    void Save() const override;
    void Print() const override;

    // Accept
    bool LetsFight(NPC* other) override;
    // Visit
    bool Defend(NPC* other) override;
};