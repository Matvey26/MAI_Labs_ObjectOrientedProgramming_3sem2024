#pragma once

#include <string>

class IGameObjectObserver {
public:
    virtual void Update(const std::string& message) = 0;
    virtual ~IGameObjectObserver() = default;
};