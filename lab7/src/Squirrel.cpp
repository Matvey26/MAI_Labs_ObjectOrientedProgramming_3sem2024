#include "../include/Squirrel.hpp"
#include <iostream>

Squirrel::Squirrel(const Point& position, bool is_alive)
  : NPC("Squirrel", position, 5.0, 5.0, is_alive) {}

// Accept
bool Squirrel::CanFight(NPC* other) {
    return !other->CanDefend(this);
}

// Visit
bool Squirrel::CanDefend(NPC* other) {
    return true;
}