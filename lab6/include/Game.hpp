#pragma once

#include "GameObject.hpp"
#include <unordered_set>
#include <memory>

class Game {
private:
    std::unordered_set<std::shared_ptr<GameObject>> game_objects_;

public:
    void SaveObjects() const;
    void PrintObjects() const;
    
    void AddObject(std::shared_ptr<GameObject> object);
    void DeleteObject(std::shared_ptr<GameObject> object);

    void StartBattle(double distance);
};
