#include "../include/NPC.hpp"

NPC::NPC(const std::string& type, const Point& pos, double travel_len, double killing_dist, bool is_alive)
    : GameObject(pos)
    , type_(type)
    , max_travel_length_(travel_len)
    , killing_distance_(killing_dist)
    , is_alive_(is_alive) {}

std::string NPC::GetType() const {
    return type_;
}

bool NPC::IsAlive() const {
    return this->is_alive_;
}

double NPC::GetMaxTravelLength() const {
    return this->max_travel_length_;
}