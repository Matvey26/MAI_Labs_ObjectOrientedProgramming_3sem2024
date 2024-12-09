#include <iostream>
#include <Game.hpp>
#include <NPCFactory.hpp>
#include <GameObjectObservers.hpp>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

int main() {
    Game game;
    game.AddObject(NPCFactory::CreateNPC("Squirrel", {1, 1}));
    game.AddObject(NPCFactory::CreateNPC("Squirrel", {1, 2}));
    game.AddObject(NPCFactory::CreateNPC("Squirrel", {2, 1}));
    game.AddObject(NPCFactory::CreateNPC("Druid", {10, 32}));
    game.AddObject(NPCFactory::CreateNPC("Druid", {21, 14}));
    game.AddObject(NPCFactory::CreateNPC("Druid", {2, 3}));
    game.AddObject(NPCFactory::CreateNPC("Druid", {17, 5}));
    game.AddObject(NPCFactory::CreateNPC("Werewolf", {5, 3}));
    game.AddObject(NPCFactory::CreateNPC("Werewolf", {8, 1}));
    game.AddObject(NPCFactory::CreateNPC("Werewolf", {9, 12}));

    game.AttachObserver(std::make_shared<LogGameObjectObserver>("/workspaces/MAI_OOP_3sem2024/tmp.txt"));

    std::thread fight_thread([&game](){
        // while (true) {
            game.StartBattle();
            std::this_thread::sleep_for(1000ms);
        // }
    });

    std::thread movement_thread([&game](){
        // while (true) {
            game.StartMovement();
            std::this_thread::sleep_for(100ms);
        // }
    });

    // while (true) {
        game.PrintObjs();
        std::this_thread::sleep_for(100ms);
    // }

    fight_thread.join();
    movement_thread.join();

    game.ClearObjects();

    return 0;
}