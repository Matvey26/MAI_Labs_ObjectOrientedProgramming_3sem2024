#include "../include/Werewolf.hpp"
#include <iostream>

Werewolf::Werewolf(const Point& position, bool is_alive)
  : NPC("Werewolf", position, 40.0, 5.0, is_alive) {}

// Accept
bool Werewolf::CanFight(NPC* other) {
    return !other->CanDefend(this);
}

// Visit
bool Werewolf::CanDefend(NPC* other) {
    if (other->GetType() == "Squirrel") {
        return false;
    }
    return true;
}