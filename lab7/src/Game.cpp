#include "../include/Game.hpp"
#include "../include/NPC.hpp"
#include <iostream>
#include <mutex>
#include <array>
#include <random>
#include <cmath>
#include <vector>

void Game::AttachObserver(std::shared_ptr<IGameObjectObserver> observer) {
    std::lock_guard<std::mutex> lock(this->common_observers_mutex_);
    this->common_observers_.push_back(observer);
    for (auto& i : this->game_objects_) {
        i->AttachObserver(observer);
    }
}

void Game::AddObject(std::shared_ptr<GameObject> object) {
    std::lock_guard<std::mutex> lock(this->game_objects_mutex_);
    this->game_objects_.insert(object);
    for (auto& obs : this->common_observers_) {
        object->AttachObserver(obs);
    }
}

void Game::DeleteObject(std::shared_ptr<GameObject> object) {
    std::lock_guard<std::mutex> lock(this->game_objects_mutex_);
    this->game_objects_.erase(object);
}

void Game::PrintObjs() {
    std::lock_guard<std::mutex> lock(this->game_objects_mutex_);
    std::vector<std::vector<char>> field(this->MAX_FIELD_SIZE, std::vector<char>(this->MAX_FIELD_SIZE, '.'));

    for (auto& obj : this->game_objects_) {
        Point pos = obj->GetPosition();

        // Приведение позиции к координатам на поле
        int x = static_cast<int>(pos.GetX());
        int y = static_cast<int>(pos.GetY());

        if (x >= this->MIN_FIELD_SIZE && x < this->MAX_FIELD_SIZE && y >= this->MIN_FIELD_SIZE && y < this->MAX_FIELD_SIZE) {
            std::shared_ptr<NPC> npc = std::dynamic_pointer_cast<NPC>(obj);
            if (npc) {
                // Используем первый символ типа NPC
                field[y][x] = npc->GetType()[0];
            } else {
                field[y][x] = '#';  // Прочие объекты
            }
        }
    }

    // Вывод игрового поля
    std::cout << "Игровое поле:\n";
    for (const auto& row : field) {
        for (char cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}

void Game::StartMovement() {
    std::lock_guard<std::mutex> lock(this->game_objects_mutex_);
    std::cout << "StartMovement!\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> angle_dist(0, 2 * M_PI);
    std::uniform_real_distribution<> distance_dist(0, 1);

    for (auto& obj : this->game_objects_) {
        std::shared_ptr<NPC> npc = std::dynamic_pointer_cast<NPC>(obj);
        if (!npc || !npc->IsAlive()) continue;

        // Генерируем случайные угол и расстояние
        double angle = angle_dist(gen);
        double distance = distance_dist(gen) * npc->GetMaxTravelLength();

        // Считаем смещение
        Point displacement(std::cos(angle) * distance, std::sin(angle) * distance);

        // Устанавливаем новую позицию
        Point new_position = npc->GetPosition() + displacement;
        npc->SetPosition(new_position, this->MIN_FIELD_SIZE, this->MAX_FIELD_SIZE);
    }
}

void Game::StartBattle() {
    std::lock_guard<std::mutex> lock(this->game_objects_mutex_);
    std::cout << "StartBattle!\n";
    // for (auto& i : this->game_objects_) {
    //     std::shared_ptr<NPC> i_npc = std::dynamic_pointer_cast<NPC>(i);
    //     if (!i_npc) continue;

    //     for (auto& j : this->game_objects_) {
    //         if (i == j) continue;

    //         std::shared_ptr<NPC> j_npc = std::dynamic_pointer_cast<NPC>(j);
    //         if (!j_npc) continue;
    //         if (!i_npc->IsAlive() or !j_npc->IsAlive()) continue;
    //         if ((i_npc->GetPosition() - j_npc->GetPosition()).Length() > distance) continue;

    //         // Само сражение
    //         i_npc->LetsFight(j_npc.get());
    //         j_npc->LetsFight(i_npc.get());

    //         // Оповещение
    //         auto make_message = [](std::shared_ptr<NPC> npc_win, std::shared_ptr<NPC> npc_lose){
    //             std::string name_win = npc_win->GetType() + '_' + std::to_string(npc_win->GetId());
    //             std::string name_lose = npc_lose->GetType() + '_' + std::to_string(npc_lose->GetId());
    //             return "NPC " + name_lose + " was defeated by NPC " + name_win;
    //         };
    //         if (!i_npc->IsAlive()) {
    //             i_npc->Notify(make_message(j_npc, i_npc));
    //         }
    //         if (!j_npc->IsAlive()) {
    //             j_npc->Notify(make_message(i_npc, j_npc));
    //         }
    //     }
    // }
}