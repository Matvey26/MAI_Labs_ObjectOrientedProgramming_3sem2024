#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <Game.hpp>
#include <NPCFactory.hpp>
#include <GameObjectObservers.hpp>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

class GameFixture : public ::testing::Test {
protected:
    Game game;
    std::fstream tmp_begin;
    std::fstream tmp_end;

    void SetUp() override {
        game.AddObject(NPCFactory::CreateNPC("Squirrel", {1, 1}));
        game.AddObject(NPCFactory::CreateNPC("Druid", {5, 5}));
        game.AddObject(NPCFactory::CreateNPC("Werewolf", {1, 5}));

        std::fstream log("log.txt", std::ios::in | std::ios::out);
        log.clear();
        log.close();

        game.AttachObserver(std::make_shared<LogGameObjectObserver>("log.txt"));

        tmp_begin.open("tmp_begin.txt");
        tmp_end.open("tmp_end.txt");
    }

    void TearDown() override {
        game.ClearObjects();
    }
};

TEST_F(GameFixture, ComplexTest) {
    // Пишем начальное состояние поля
    game.PrintObjs(tmp_begin);

    std::thread fight_thread([&](){
        game.StartBattle();
        std::this_thread::sleep_for(100ms);      
    });

    std::thread movement_thread([&](){
        game.StartMovement();
        std::this_thread::sleep_for(100ms);
    });

    fight_thread.join();
    movement_thread.join();

    // Пишем состояние поля после передвижений и сражений
    game.PrintObjs(tmp_end);

    std::vector<std::vector<char>> field_begin(101, std::vector<char>(101));
    for (int i = 0; i <= 100; ++i) {
        for (int j = 0; j <= 100; ++j) {
            tmp_begin >> field_begin[i][j];
        }
    }
    std::vector<std::vector<char>> field_end(101, std::vector<char>(101));
    for (int i = 0; i <= 100; ++i) {
        for (int j = 0; j <= 100; ++j) {
            tmp_end >> field_end[i][j];
        }
    }

    Point s_begin{0, 0}, s_end{0, 0};
    Point w_begin{0, 0}, w_end{0, 0};
    Point d_begin{0, 0}, d_end{0, 0};
    for (int x = 0; x <= 100; ++x) {
        for (int y = 0; y <= 100; ++y) {
            if (field_begin[y][x] == 'S') {
                s_begin = Point{x, y};
            }
            if (field_begin[y][x] == 'W') {
                w_begin = Point{x, y};
            }
            if (field_begin[y][x] == 'D') {
                d_begin = Point{x, y};
            }

            if (field_end[y][x] == 'S') {
                s_end = Point{x, y};
            }
            if (field_end[y][x] == 'W') {
                w_end = Point{x, y};
            }
            if (field_end[y][x] == 'D') {
                d_end = Point{x, y};
            }
        }
    }

    ASSERT_TRUE((s_begin - s_end).Length() <= 5.0);
    ASSERT_TRUE((w_begin - w_end).Length() <= 40.0);
    ASSERT_TRUE((d_begin - d_end).Length() <= 10.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}