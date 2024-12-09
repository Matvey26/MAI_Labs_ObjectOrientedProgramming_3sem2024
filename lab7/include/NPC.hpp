#pragma once

#include "GameObject.hpp"
#include <string>

class NPC : public GameObject {
protected:
    std::string type_;
    bool is_alive_;
    double max_travel_length_;
    double killing_distance_;

public:
    NPC(const std::string& type, const Point& pos, double travel_len, double killing_dist, bool is_alive = true);

    std::string GetType() const;
    bool IsAlive() const;
    double GetMaxTravelLength() const;
    double GetKillingDistance() const;
    void Die();

/*
Класс NPC одновременно visitor и acceptor.  
*/

    // Accept
    virtual bool CanFight(NPC* other) = 0;
    // Visit
    virtual bool CanDefend(NPC* other) = 0;
};