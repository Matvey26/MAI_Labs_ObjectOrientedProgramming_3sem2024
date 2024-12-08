#pragma once

#include "GameObject.hpp"
#include "GameObjectObservers.hpp"
#include <unordered_set>
#include <memory>
#include <vector>
#include <mutex>

class Game {
private:
    std::mutex game_objects_mutex_;
    std::mutex common_observers_mutex_;
    std::unordered_set<std::shared_ptr<GameObject>> game_objects_;
    std::vector<std::shared_ptr<IGameObjectObserver>> common_observers_;

    constexpr static double MIN_FIELD_SIZE = 0.0;
    constexpr static double MAX_FIELD_SIZE = 30.0;

public:
    void AttachObserver(std::shared_ptr<IGameObjectObserver> observer);

    void AddObject(std::shared_ptr<GameObject> object);
    void DeleteObject(std::shared_ptr<GameObject> object);

    void PrintObjs();
    void StartMovement();
    void StartBattle();
};
