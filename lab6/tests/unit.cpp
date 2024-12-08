#include <gtest/gtest.h>
#include "../include/NPCFactory.hpp"
#include "../include/Game.hpp"
#include "../include/GameObject.hpp"
#include "../include/GameObjectObservers.hpp"
#include "../include/Werewolf.hpp"
#include "../include/Druid.hpp"
#include "../include/Squirrel.hpp"
#include "../include/Point.hpp"
#include <cmath>

// Тест создания NPC через фабрику
TEST(NPCFactoryTest, CreateNPC) {
    // Создаем несколько NPC объектов
    auto squirrel = NPCFactory::CreateNPC("Squirrel", {1.0, 2.0});
    auto werewolf = NPCFactory::CreateNPC("Werewolf", {3.0, 4.0});
    auto druid = NPCFactory::CreateNPC("Druid", {5.0, 6.0});

    // Проверка типов
    EXPECT_EQ(squirrel->GetType(), "Squirrel");
    EXPECT_EQ(werewolf->GetType(), "Werewolf");
    EXPECT_EQ(druid->GetType(), "Druid");

    // Проверка координат
    EXPECT_EQ(squirrel->GetPosition(), Point(1.0, 2.0));
    EXPECT_EQ(werewolf->GetPosition(), Point(3.0, 4.0));
    EXPECT_EQ(druid->GetPosition(), Point(5.0, 6.0));
}

// Тест на бой между NPC
TEST(NPCTest, FightBetweenNPCs) {
    auto squirrel = NPCFactory::CreateNPC("Squirrel", {1.0, 1.0});
    auto werewolf = NPCFactory::CreateNPC("Werewolf", {1.0, 2.0});

    // Проверяем, что оба NPC живы до сражения
    EXPECT_TRUE(squirrel->IsAlive());
    EXPECT_TRUE(werewolf->IsAlive());

    squirrel->LetsFight(werewolf.get());
    werewolf->LetsFight(squirrel.get());

    EXPECT_TRUE(squirrel->IsAlive());
    EXPECT_FALSE(werewolf->IsAlive());
}

// Тест на корректность работы observers
TEST(GameTest, ObserverNotification) {
    // Создаем объекты NPC
    auto squirrel = NPCFactory::CreateNPC("Squirrel", {1.0, 1.0});
    auto werewolf = NPCFactory::CreateNPC("Werewolf", {2.0, 2.0});

    // Создаем observers
    auto log_obs = std::make_shared<LogGameObjectObserver>("./logs/test_log.txt");
    auto print_obs = std::make_shared<PrintGameObjectObserver>();

    // Создаем игру и добавляем наблюдателей
    Game game;
    game.AttachObserver(log_obs);
    game.AttachObserver(print_obs);

    // Добавляем объекты в игру
    game.AddObject(squirrel);
    game.AddObject(werewolf);

    // Начинаем сражение
    game.StartBattle(2.0);

    // Ожидаем, что сражение вызовет уведомления (вывод в консоль и в файл)
    // Проверка ручная
    // >>> NPC Werewolf_7 was defeated by NPC Squirrel_6
}

// Тест на правильность работы с `Point` (например, расстояние)
TEST(PointTest, Distance) {
    Point p1(1.0, 1.0);
    Point p2(4.0, 5.0);

    EXPECT_DOUBLE_EQ(p1.Length(), std::sqrt(1.0 * 1.0 + 1.0 * 1.0));
    EXPECT_DOUBLE_EQ(p2.Length(), std::sqrt(4.0 * 4.0 + 5.0 * 5.0));
    EXPECT_DOUBLE_EQ(p1.Length(), std::sqrt(2.0));
    EXPECT_DOUBLE_EQ(p2.Length(), std::sqrt(41.0));
}

// Тест на создание объекта и его позицию
TEST(GameObjectTest, PositionAndId) {
    GameObject obj1(Point(3.0, 3.0));
    GameObject obj2(Point(4.0, 5.0));

    EXPECT_EQ(obj1.GetPosition(), Point(3.0, 3.0));
    EXPECT_EQ(obj2.GetPosition(), Point(4.0, 5.0));
    EXPECT_NE(obj1.GetId(), obj2.GetId());
}

// Тест на создание NPC и сражение с несколькими NPC
TEST(GameTest, MultipleFights) {
    // Создаем несколько NPC объектов
    auto squirrel = NPCFactory::CreateNPC("Squirrel", {1.0, 1.0});
    auto werewolf = NPCFactory::CreateNPC("Werewolf", {2.0, 2.0});
    auto druid = NPCFactory::CreateNPC("Druid", {3.0, 3.0});

    // Создаем игру
    Game game;
    game.AddObject(squirrel);
    game.AddObject(werewolf);
    game.AddObject(druid);

    // Проверка на начальное состояние
    EXPECT_TRUE(squirrel->IsAlive());
    EXPECT_TRUE(werewolf->IsAlive());
    EXPECT_TRUE(druid->IsAlive());

    // Сражение на определенной дистанции
    game.StartBattle(2.0);

    // После боя, проверяем, кто выжил
    EXPECT_TRUE(squirrel->IsAlive());
    EXPECT_FALSE(werewolf->IsAlive());
    EXPECT_FALSE(druid->IsAlive());
}

