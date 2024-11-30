#include "../include/Druid.hpp"
#include <iostream>

Druid::Druid(const Point& position) : NPC("Druid", position) {}

void Druid::Save() const {
    // Not implemented
}

void Druid::Print() const {
    std::cout << this->GetType() << '_' << this->GetId();
    if (!this->IsAlive()) {
        std::cout << "(dead)";
    }
}

// Accept
bool Druid::LetsFight(NPC* other) {
    return !other->Defend(this);
}

// Visit
bool Druid::Defend(NPC* other) {
    bool result = this->is_alive_;
    if (other->GetType() == "Squirrel") {
        result = false;
    } else if (other->GetType() == "Werewolf") {
        result = false;
    }

    this->is_alive_ = result;
    return result;
}