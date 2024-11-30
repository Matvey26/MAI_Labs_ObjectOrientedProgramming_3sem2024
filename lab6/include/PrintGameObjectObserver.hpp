#pragma once

#include "IGameObjectObserver.hpp"
#include <string>

class PrintGameObjectObserver : public IGameObjectObserver {
public:
    PrintGameObjectObserver();

    void Update(const std::string& message) override;
};