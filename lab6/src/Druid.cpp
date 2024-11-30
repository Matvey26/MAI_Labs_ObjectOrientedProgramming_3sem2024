#pragma once

#include "../include/Druid.hpp"
#include <iostream>

void Druid::Save() const {
    // Not implemented
}

void Druid::Print() const {
    std::cout << this->GetType() << '_' << this->GetId();
}

// Accept
bool Druid::LetsFight(NPC* other) {
    return !other->Defend(this);
}

// Visit
bool Druid::Defend(NPC* other) {
    if (other->GetType() == "Squirrel") {
        return false;
    } else if (other->GetType() == "Werewolf") {
        return false;
    }

    return true;
}