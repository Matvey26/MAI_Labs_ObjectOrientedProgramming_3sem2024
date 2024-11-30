#include <iostream>
#include "include/Game.hpp"
#include "include/Squirrel.hpp"
#include "include/Werewolf.hpp"
#include "include/Druid.hpp"
#include <memory>

int main() {
    std::shared_ptr<NPC> s1{new Squirrel({10, 5})};
    std::shared_ptr<NPC> s2{new Squirrel({12, 9})};
    std::shared_ptr<NPC> w1(new Werewolf({9, 14}));
    std::shared_ptr<NPC> d1(new Druid({10, 12}));
    Game game;
    game.AddObject(s1);
    game.AddObject(s2);
    game.AddObject(w1);
    game.AddObject(d1);
    game.PrintObjects();
    game.StartBattle(3);
    game.PrintObjects();
}