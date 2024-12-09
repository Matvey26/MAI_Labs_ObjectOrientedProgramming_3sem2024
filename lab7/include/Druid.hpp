#pragma once

#include "NPC.hpp"
#include <memory>

class Druid : public NPC {
public:
    Druid(const Point& position, bool is_alive = true);

    // Accept
    bool CanFight(NPC* other) override;
    // Visit
    bool CanDefend(NPC* other) override;
};