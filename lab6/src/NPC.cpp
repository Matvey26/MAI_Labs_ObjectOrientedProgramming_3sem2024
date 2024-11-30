#include "../include/NPC.hpp"

NPC::NPC(const std::string& type, const Point& pos) : GameObject(pos), type_(type), is_alive_(true) {}

std::string NPC::GetType() const {
    return type_;
}

bool NPC::IsAlive() const {
    return this->is_alive_;
}