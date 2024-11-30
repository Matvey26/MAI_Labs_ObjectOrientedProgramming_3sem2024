#pragma once

#include "INPC.hpp"
#include <memory>

class Werewolf : public INPC {
public:
    Werewolf() : INPC("Werewolf") {}

    void Save() const override;
    void Print() const override;

    // Accept
    bool LetsFight(INPC* other) override;
    // Visit
    bool Defend(INPC* other) override;
};