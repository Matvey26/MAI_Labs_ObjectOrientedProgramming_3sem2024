#pragma once

#include "../include/Werewolf.hpp"
#include <iostream>

void Werewolf::Save() const {
    // Not implemented
}

void Werewolf::Print() const {
    std::cout << this->GetType() << '_' << this->GetId();
}

// Accept
bool Werewolf::LetsFight(NPC* other) {
    return !other->Defend(this);
}

// Visit
bool Werewolf::Defend(NPC* other) {
    if (other->GetType() == "Squirrel") {
        return false;
    }

    return true;
}