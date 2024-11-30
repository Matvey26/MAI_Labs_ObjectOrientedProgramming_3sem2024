#include "../include/Squirrel.hpp"
#include <iostream>

Squirrel::Squirrel(const Point& position) : NPC("Squirrel", position) {}

void Squirrel::Save() const {
    // Not implemented
}

void Squirrel::Print() const {
    std::cout << this->GetType() << '_' << this->GetId();
    if (!this->IsAlive()) {
        std::cout << "(dead)";
    }
}

// Accept
bool Squirrel::LetsFight(NPC* other) {
    return !other->Defend(this);
}

// Visit
bool Squirrel::Defend(NPC* other) {
    return true;
}