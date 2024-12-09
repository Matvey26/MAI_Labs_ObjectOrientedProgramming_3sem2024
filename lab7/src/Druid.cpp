#include "../include/Druid.hpp"
#include <iostream>

Druid::Druid(const Point& position, bool is_alive)
  : NPC("Druid", position, 10.0, 10.0, is_alive) {}

// Accept
bool Druid::CanFight(NPC* other) {
    return !other->CanDefend(this);
}

// Visit
bool Druid::CanDefend(NPC* other) {
    if (other->GetType() == "Squirrel") {
        return false;
    } else if (other->GetType() == "Werewolf") {
        return false;
    }
    return true;
}