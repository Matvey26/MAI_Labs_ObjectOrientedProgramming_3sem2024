#pragma once

#include "../include/NPC.hpp"

NPC::NPC(const std::string& type) : GameObject(), type_(type) {}

std::string NPC::GetType() const {
    return type_;
}