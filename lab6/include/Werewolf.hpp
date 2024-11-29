#pragma once

#include "INPC.hpp"
#include <memory>

class Werewolf : public INPC {
public:
    Werewolf() : INPC("Werewolf") {}

    void Save() const override;
    void Print() const override;
};