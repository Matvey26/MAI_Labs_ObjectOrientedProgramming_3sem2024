#pragma once

#include "INPC.hpp"
#include <memory>

class Squirrel : public INPC {
public:
    Squirrel() : INPC("Squirrel") {}

    void Save() const override;
    void Print() const override;
};