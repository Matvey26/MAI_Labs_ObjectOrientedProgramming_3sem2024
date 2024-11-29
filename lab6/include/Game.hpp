#pragma once

#include "GameObject.hpp"
#include "IGameVisitor.hpp"
#include <vector>
#include <memory>

class Game {
private:
    std::vector<std::unique_ptr<GameObject>> game_objects_;

public:
    void SaveObjects() const;
    void PrintObjects() const;
    
    void AddObject(const GameObject& object);
    void DeleteObject(int id);

    void Accept(IGameVisitor& visitor);
};