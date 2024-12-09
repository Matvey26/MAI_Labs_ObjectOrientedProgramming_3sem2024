#pragma once

#include "NPC.hpp"
#include <memory>

class Werewolf : public NPC {
public:
    Werewolf(const Point& position, bool is_alive = true);

    // Accept
    bool CanFight(NPC* other) override;
    // Visit
    bool CanDefend(NPC* other) override;
};