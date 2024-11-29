#pragma once

#include "IGameVisitor.hpp"
#include "Game.hpp"

class BattleGameVisitor : public IGameVisitor {
    void Visit(Game& game);
};