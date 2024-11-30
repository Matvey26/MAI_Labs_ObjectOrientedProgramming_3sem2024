#include "../include/Werewolf.hpp"
#include <iostream>

Werewolf::Werewolf(const Point& position) : NPC("Werewolf", position) {}

void Werewolf::Save() const {
    // Not implemented
}

void Werewolf::Print() const {
    std::cout << this->GetType() << '_' << this->GetId();
    if (!this->IsAlive()) {
        std::cout << "(dead)";
    }
}

// Accept
bool Werewolf::LetsFight(NPC* other) {
    return !other->Defend(this);
}

// Visit
bool Werewolf::Defend(NPC* other) {
    bool result = this->is_alive_;
    if (other->GetType() == "Squirrel") {
        result = false;
    }

    this->is_alive_ = result;
    return result;
}