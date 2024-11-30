#pragma once

#include "NPC.hpp"
#include <memory>

class Werewolf : public NPC {
public:
    Werewolf(const Point& position);

    void Save() const override;
    void Print() const override;

    // Accept
    bool LetsFight(NPC* other) override;
    // Visit
    bool Defend(NPC* other) override;
};