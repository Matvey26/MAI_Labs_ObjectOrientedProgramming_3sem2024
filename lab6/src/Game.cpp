#include "../include/Game.hpp"
#include "../include/NPC.hpp"
#include <iostream>

void Game::SaveObjects() const {
    // Not implemented
}

void Game::PrintObjects() const {
    std::cout << "RPG Game.\n";
    std::cout << "Game objects: {\n";
    int number = 0;
    for (auto i : this->game_objects_) {
        std::cout << "    " << ++number << ". ";
        i->Print();
        std::cout << '\n';
    }
    std::cout << '}' << std::endl;
}

void Game::AddObject(std::shared_ptr<GameObject> object) {
    this->game_objects_.insert(object);
}

void Game::DeleteObject(std::shared_ptr<GameObject> object) {
    this->game_objects_.erase(object);
}

void Game::StartBattle(double distance) {
    for (auto& i : this->game_objects_) {
        std::shared_ptr<NPC> i_npc = std::dynamic_pointer_cast<NPC>(i);
        if (!i_npc) continue;

        for (auto& j : this->game_objects_) {
            if (i == j) continue;

            std::shared_ptr<NPC> j_npc = std::dynamic_pointer_cast<NPC>(j);
            if (!j_npc) continue;

            if (!i_npc->IsAlive() or !j_npc->IsAlive()) continue;

            if ((i_npc->GetPosition() - j_npc->GetPosition()).Length() > distance) continue;

            i_npc->LetsFight(j_npc.get());
            j_npc->LetsFight(i_npc.get());
        }
    }
}