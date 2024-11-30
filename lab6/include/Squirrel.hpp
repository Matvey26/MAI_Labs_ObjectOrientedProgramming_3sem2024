#pragma once

#include "NPC.hpp"
#include <memory>

class Squirrel : public NPC {
public:
    Squirrel(const Point& position);

    void Save() const override;
    void Print() const override;

    // Accept
    bool LetsFight(NPC* other) override;
    // Visit
    bool Defend(NPC* other) override;
};