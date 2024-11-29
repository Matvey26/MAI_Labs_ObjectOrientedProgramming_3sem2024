#pragma once

#include "GameObject.hpp"
#include <string>

class INPC : public GameObject {
protected:
    std::string type_;

public:
    INPC(const std::string& type) : GameObject(), type_(type) {}

    virtual void Save() const = 0;
    virtual void Print() const = 0;

    std::string GetType() const;
};