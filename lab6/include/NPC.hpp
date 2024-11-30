#pragma once

#include "GameObject.hpp"
#include <string>

class NPC : public GameObject {
protected:
    std::string type_;

public:
    NPC(const std::string& type) : GameObject(), type_(type) {}

    virtual void Save() const = 0;
    virtual void Print() const = 0;

    std::string GetType() const;

/*
Класс NPC одновременно visitor и acceptor.  
*/

    // Accept
    virtual bool LetsFight(NPC* other) = 0;
    // Visit
    virtual bool Defend(NPC* other) = 0;
};