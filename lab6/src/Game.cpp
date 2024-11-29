#pragma once

#include "../include/Game.hpp"

void Game::SaveObjects() const {
    // Not implemented
}

void Game::PrintObjects() const {
    // Not implemented
}

void Game::AddObject(const GameObject& object) {
    // Not implemented
}

void Game::DeleteObject(int id) {
    // Not implemented
}

void Game::Accept(IGameVisitor& visitor) {
    visitor.Visit(*this);
}
