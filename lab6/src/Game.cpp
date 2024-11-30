#pragma once

#include "../include/Game.hpp"
#include "../include/NPC.hpp"

void Game::SaveObjects() const {
    // Not implemented
}

void Game::PrintObjects() const {
    // Not implemented
}

void Game::AddObject(std::shared_ptr<GameObject> object) {
    this->game_objects_.insert(object);
}

void Game::DeleteObject(std::shared_ptr<GameObject> object) {
    this->game_objects_.erase(object);
}

void Game::StartBattle() {
    std::unordered_set<std::shared_ptr<GameObject>> updated_game_objs(this->game_objects_);
    for (auto i : this->game_objects_) {
        for (auto j : this->game_objects_) {
            
        }
    }
}