#pragma once

#include "NPC.hpp"
#include <memory>

class Squirrel : public NPC {
public:
    Squirrel(const Point& position, bool is_alive = true);

    // Accept
    bool CanFight(NPC* other) override;
    // Visit
    bool CanDefend(NPC* other) override;
};