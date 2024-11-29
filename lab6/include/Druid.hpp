#pragma once

#include "INPC.hpp"
#include <memory>

class Druid : public INPC {
public:
    Druid() : INPC("Druid") {}

    void Save() const override;
    void Print() const override;
};