#pragma once

#include "../include/Squirrel.hpp"
#include <iostream>

void Squirrel::Save() const {
    // Not implemented
}

void Squirrel::Print() const {
    std::cout << this->GetType() << '_' << this->GetId();
}

// Accept
bool Squirrel::LetsFight(NPC* other) {
    return !other->Defend(this);
}

// Visit
bool Squirrel::Defend(NPC* other) {
    return true;
}