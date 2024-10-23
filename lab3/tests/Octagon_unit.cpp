#include <gtest/gtest.h>
#include "Octagon.hpp"
#include <stdexcept>

// Тестирование конструктора по умолчанию
TEST(OctagonTest, DefaultConstructor) {
    Octagon o;
    EXPECT_EQ(o.GetVerticesNumber(), 8);  // Количество вершин должно быть 8
}

// Тестирование конструктора с использованием списков инициализации
TEST(OctagonTest, InitializerListConstructor) {
    Octagon o = { {0.0, 0.0}, {1.0, 0.0}, {2.0, 1.0}, {2.0, 2.0}, 
                  {1.0, 3.0}, {0.0, 3.0}, {-1.0, 2.0}, {-1.0, 1.0} };

    EXPECT_EQ(o.GetVerticesNumber(), 8); // Должно быть 8 вершин
    Point* vertices = o.GetVertices();
    EXPECT_EQ(vertices[0], Point(0.0, 0.0));
    EXPECT_EQ(vertices[1], Point(1.0, 0.0));
    EXPECT_EQ(vertices[2], Point(2.0, 1.0));
    EXPECT_EQ(vertices[3], Point(2.0, 2.0));
    EXPECT_EQ(vertices[4], Point(1.0, 3.0));
    EXPECT_EQ(vertices[5], Point(0.0, 3.0));
    EXPECT_EQ(vertices[6], Point(-1.0, 2.0));
    EXPECT_EQ(vertices[7], Point(-1.0, 1.0));
}

TEST(OctagonTest, WrongInitializerListConstructor) {
    EXPECT_THROW(Octagon o({{0.0, 1.0}, {1.0, 0.0}}), std::runtime_error);
}

// Тестирование конструктора копирования
TEST(OctagonTest, CopyConstructor) {
    Octagon o1 = { {0.0, 0.0}, {1.0, 0.0}, {2.0, 1.0}, {2.0, 2.0}, 
                   {1.0, 3.0}, {0.0, 3.0}, {-1.0, 2.0}, {-1.0, 1.0} };

    Octagon o2(o1); // Копируем
    EXPECT_EQ(o2.GetVerticesNumber(), 8); // Количество вершин должно совпадать
    for (size_t i = 0; i < 8; ++i) {
        EXPECT_EQ(o2.GetVertices()[i], o1.GetVertices()[i]); // Проверяем координаты
    }
}

// Тестирование оператора присваивания
TEST(OctagonTest, CopyAssignmentOperator) {
    Octagon o1 = { {0.0, 0.0}, {1.0, 0.0}, {2.0, 1.0}, {2.0, 2.0}, 
                   {1.0, 3.0}, {0.0, 3.0}, {-1.0, 2.0}, {-1.0, 1.0} };

    Octagon o2; // Создаем новый октон
    o2 = o1; // Присваиваем
    EXPECT_EQ(o2.GetVerticesNumber(), 8); // Количество вершин должно совпадать
    for (size_t i = 0; i < 8; ++i) {
        EXPECT_EQ(o2.GetVertices()[i], o1.GetVertices()[i]); // Проверяем координаты
    }
}

// Тестирование оператора ввода
TEST(OctagonTest, InputOperator) {
    std::istringstream input("0.0 0.0\n1.0 0.0\n2.0 1.0\n2.0 2.0\n1.0 3.0\n0.0 3.0\n-1.0 2.0\n-1.0 1.0\n");
    Octagon o;
    input >> o;

    EXPECT_EQ(o.GetVerticesNumber(), 8); // Должно быть 8 вершин
    Point* vertices = o.GetVertices();
    EXPECT_EQ(vertices[0], Point(0.0, 0.0));
    EXPECT_EQ(vertices[1], Point(1.0, 0.0));
    EXPECT_EQ(vertices[2], Point(2.0, 1.0));
    EXPECT_EQ(vertices[3], Point(2.0, 2.0));
    EXPECT_EQ(vertices[4], Point(1.0, 3.0));
    EXPECT_EQ(vertices[5], Point(0.0, 3.0));
    EXPECT_EQ(vertices[6], Point(-1.0, 2.0));
    EXPECT_EQ(vertices[7], Point(-1.0, 1.0));
}

// Тестирование оператора вывода
TEST(OctagonTest, OutputOperator) {
    Octagon o = { {0.0, 0.0}, {1.0, 0.0}, {2.0, 1.0}, {2.0, 2.0}, 
                  {1.0, 3.0}, {0.0, 3.0}, {-1.0, 2.0}, {-1.0, 1.0} };

    std::ostringstream output;
    output << o;
    EXPECT_EQ(output.str(), "Octagon(Point(0, 0), Point(1, 0), Point(2, 1), Point(2, 2), Point(1, 3), Point(0, 3), Point(-1, 2), Point(-1, 1))");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}