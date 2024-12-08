#include "../include/Squirrel.hpp"
#include <iostream>

Squirrel::Squirrel(const Point& position, bool is_alive)
  : NPC("Squirrel", position, is_alive) {}

// Accept
bool Squirrel::LetsFight(NPC* other) {
    return !other->Defend(this);
}

// Visit
bool Squirrel::Defend(NPC* other) {
    return true;
}