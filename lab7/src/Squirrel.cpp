#include "../include/Squirrel.hpp"
#include <iostream>

Squirrel::Squirrel(const Point& position, bool is_alive)
  : NPC("Squirrel", position, 5.0, 5.0, is_alive) {}

// Accept
bool Squirrel::LetsFight(NPC* other) {
    return !other->Defend(this);
}

// Visit
bool Squirrel::Defend(NPC* other) {
    return true;
}