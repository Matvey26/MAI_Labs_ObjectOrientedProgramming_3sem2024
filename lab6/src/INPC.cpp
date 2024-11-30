#pragma once

#include "../include/INPC.hpp"

INPC::INPC(const std::string& type) : GameObject(), type_(type) {}

std::string INPC::GetType() const {
    return type_;
}
